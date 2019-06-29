#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->lineEditCodigo->setFocus();
    QWidget::setTabOrder(ui->lineEditCodigo, ui->lineEditQuantidade);
    QWidget::setTabOrder(ui->lineEditQuantidade, ui->lineEditReceber);

    { //SINAIS
    connect(ui->lineEditQuantidade, SIGNAL(returnPressed()), this, SLOT(preencheLinha()));
    connect(ui->lineEditQuantidade, SIGNAL(returnPressed()), this, SLOT(preencheValorTotal()));
    connect(ui->lineEditQuantidade, SIGNAL(returnPressed()), this, SLOT(resetaQuantidade()));

    connect(ui->lineEditCodigo, SIGNAL(returnPressed()), this, SLOT(preencheLinha()));
    connect(ui->lineEditCodigo, SIGNAL(editingFinished()), this, SLOT(preencheValorUnitario()));
    connect(ui->lineEditCodigo, SIGNAL(returnPressed()), this, SLOT(preencheValorUnitario()));
    connect(ui->lineEditCodigo, SIGNAL(editingFinished()), this, SLOT(preencheValorTotal()));
    connect(ui->lineEditCodigo, SIGNAL(returnPressed()), this, SLOT(preencheValorTotal()));

    connect(ui->lineEditReceber, SIGNAL(returnPressed()), this, SLOT(calculaTroco()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::preencheLinha()
{
    QSqlQuery query;
    //QDateTime timestamp = QDateTime::currentDateTime();
    //query.prepare("INSERT INTO pedido(data_hora) VALUES(:datetime);");
    //query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));
    //query.exec();

    if(!query.exec("SELECT MAX(id_pedido) FROM pedido;"))
        QMessageBox::warning(this, "Erro", "SELECT MAX(id_pedido)!");
    else
        query.next();
    int pedidoAtual = query.value(0).toInt();

    query.prepare("SELECT COUNT(id_produto) FROM produto WHERE id_produto = :id_produto");
    query.bindValue(":id_produto", ui->lineEditCodigo->text());
    if(!query.exec())
        QMessageBox::warning(this, "Erro", "Problema no SELECT COUNT(id_produto)!");
    else
        query.next();

    int qntCodigos = query.value(0).toInt();

    if(qntCodigos == 1){

        if(ui->lineEditQuantidade->text().toFloat() > 0){
            query.prepare("INSERT INTO pedido_tem_produto VALUES (:id_pedido, :id_produto, :quantidade);");
            query.bindValue(":id_pedido", pedidoAtual);
            query.bindValue(":id_produto", ui->lineEditCodigo->text());
            query.bindValue(":quantidade", ui->lineEditQuantidade->text());
            if(!query.exec())
                QMessageBox::warning(this, "Erro", "Problema no INSERT em pedido_tem_produto!");
        }
    }

    query.prepare("SELECT Pr.nome AS \"produto\", Pr.preco, PP.quantidade, PP.quantidade * Pr.preco AS total_item FROM (pedido_tem_produto PP JOIN produto Pr ON Pr.id_produto = PP.id_produto) JOIN pedido Pe ON PP.id_pedido = Pe.id_pedido WHERE Pe.id_pedido = :id_pedido;");
    query.bindValue(":id_pedido", QString::number(pedidoAtual));
    if(query.exec()){ //preenche a tabela principal com as informações do bd
        int cont = 0;
        double subtotal = 0;
        QString subtotalQs;
        ui->tableProdutosPedido->setColumnCount(4);
        ui->tableProdutosPedido->setRowCount(0);
        ui->labelSubtotalValor->clear();
        while(query.next()){
            ui->tableProdutosPedido->insertRow(cont);
            ui->tableProdutosPedido->setRowHeight(cont, 23);
            ui->tableProdutosPedido->setItem(cont, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableProdutosPedido->setItem(cont, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableProdutosPedido->setItem(cont, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableProdutosPedido->setItem(cont, 3, new QTableWidgetItem(query.value(3).toString()));
            subtotal += query.value(3).toDouble();
            subtotalQs.setNum(subtotal);
            ui->labelSubtotalValor->setText(subtotalQs);
            cont++;
        }
        formataTabela();
    }else{
        QMessageBox::warning(this, "Erro!", "Problema ao executar a query nos pedidos!");
    }

}

void MainWindow::preencheValorUnitario()
{
    int cont = 0;

    QSqlQuery query;
    QString codigoProduto = ui->lineEditCodigo->text();
    QString valorProduto;
    query.prepare("SELECT preco FROM produto WHERE id_produto = :codigo;");
    query.bindValue(":codigo", codigoProduto);

    if(!query.exec()){
        QMessageBox::warning(this, "Erro!", "Query para achar preço do produto não executada!");
    }else{
        if(query.next()){
            cont ++;
        }
        if(cont == 1){
            valorProduto = query.value(0).toString();
            ui->labelPrecoUnitarioValor->setText(valorProduto);
        }else{
            ui->labelPrecoUnitarioValor->setText("NÃO ENCONTRADO!");
            ui->labelTotalDoItemValor->setText("NÃO ENCONTRADO!");
        }
    }
}

void MainWindow::preencheValorTotal()
{
    int cont = 0;
    double valorTotal;
    QSqlQuery query;
    QString codigoProduto = ui->lineEditCodigo->text();
    QString valorProduto;
    QString quantidade;
    query.prepare("SELECT preco FROM produto WHERE id_produto = :codigo;");
    query.bindValue(":codigo", codigoProduto);

    if(!query.exec()){
        QMessageBox::warning(this, "Erro!", "Query para achar preço do produto não executada!");
    }else{
        if(query.next()){
            cont ++;
        }
        if(cont == 1){
            valorProduto = query.value(0).toString();
            quantidade = ui->lineEditQuantidade->text();
            valorTotal = valorProduto.toDouble() * quantidade.toDouble();
            ui->labelTotalDoItemValor->setText(QString::number(valorTotal));
        }else{
            ui->labelPrecoUnitarioValor->setText("NÃO ENCONTRADO!");
        }
    }
}

void MainWindow::resetaQuantidade()
{
    ui->lineEditQuantidade->setText("1");
    ui->lineEditCodigo->setFocus();
    ui->lineEditCodigo->setText("");
}

void MainWindow::calculaTroco()
{
    double subtotal = ui->labelSubtotalValor->text().toDouble();
    double valorRecebido = ui->lineEditReceber->text().toDouble();
    double totalRecebido = ui->labelTotalRecebidoValor->text().toDouble();
    totalRecebido += valorRecebido;
    ui->labelTotalRecebidoValor->setText(QString::number(totalRecebido));

    double troco = totalRecebido - subtotal;
    if(totalRecebido > subtotal){
        QString trocoStr = QString::number(troco);
        ui->labelTrocoValor->setText(trocoStr);
    }
}

void MainWindow::setCrudEnable(bool enable)
{
    ui->actionProduto->setEnabled(enable);
    ui->actionUsuario->setEnabled(enable);
}

void MainWindow::formataTabela()
{
    QStringList nomeColunas = {"Descrição", "Preço", "Qnt", "Total"};
    ui->tableProdutosPedido->setColumnWidth(0, 200);
    ui->tableProdutosPedido->setColumnWidth(1, 40);
    ui->tableProdutosPedido->setColumnWidth(2, 35);
    ui->tableProdutosPedido->setColumnWidth(3, 35);
    ui->tableProdutosPedido->setHorizontalHeaderLabels(nomeColunas);
    ui->tableProdutosPedido->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProdutosPedido->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{

    QSqlQuery query;
    QMessageBox::StandardButton answer;
    switch(evento->key()){
        case Qt::Key_F2:
            ui->lineEditReceber->setFocus();
            ui->lineEditCodigo->setDisabled(true);
            ui->lineEditQuantidade->setDisabled(true);
            break;
        case Qt::Key_F3:
            if(ui->labelTotalRecebidoValor->text().toDouble() < ui->labelSubtotalValor->text().toDouble())
                QMessageBox::about(this, "Aviso!", "Receba o valor total do pedido antes de fechá-lo.");
            else{
                ui->lineEditCodigo->setEnabled(true);
                ui->lineEditQuantidade->setEnabled(true);
                if(!query.exec("INSERT INTO pedido(data_hora) VALUES(DATETIME(CURRENT_TIMESTAMP, 'localtime'));")){
                    QMessageBox::warning(this, "Erro!", "Query para criar novo pedido não executada");
                }
                ui->tableProdutosPedido->setRowCount(0);
                ui->lineEditReceber->clear();
                ui->lineEditCodigo->setFocus();
                ui->labelTotalRecebidoValor->setText("0");
                ui->labelTrocoValor->setText("0");
                ui->labelSubtotalValor->setText("0");
                ui->labelTotalDoItemValor->setText("0");
                ui->labelPrecoUnitarioValor->setText("0");
            }
            break;
        case Qt::Key_F12:
            answer = QMessageBox::question(this, "Aviso!", "Deseja realmente sair?", QMessageBox::Yes | QMessageBox::No);
            if(answer == QMessageBox::Yes){
                QApplication::quit();
            }
            break;
        default:
            break;
    }

}

void MainWindow::on_actionSair_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionQt_Creator_triggered()
{
    QMessageBox::aboutQt(this, "Sobre: Qt Creator");
}

void MainWindow::on_actionSorveteria_triggered()
{
    QMessageBox::about(this, "C++ Sorveteria", "SIN143 - Laboratorio de Programacao.\nIntegrantes do grupo: \nJoao\nEliezer\nMarcel.");
}

void MainWindow::on_actionProduto_triggered()
{
    CrudProdutoWindow *cpw = new CrudProdutoWindow;
    cpw->preencheTabela();
    cpw->show();
}

void MainWindow::on_actionUsuario_triggered()
{
    crudusuariowindow *cuw = new crudusuariowindow;
    cuw->preencheTabela();
    cuw->show();
}

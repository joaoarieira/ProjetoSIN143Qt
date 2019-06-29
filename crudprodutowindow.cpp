#include "crudprodutowindow.h"
#include "ui_crudprodutowindow.h"

CrudProdutoWindow::CrudProdutoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrudProdutoWindow)
{
    ui->setupUi(this);

}

CrudProdutoWindow::~CrudProdutoWindow()
{
    delete ui;
}

void CrudProdutoWindow::preencheTabela()
{
    QSqlQuery query;
    int cont = 0;
    query.prepare("SELECT * FROM produto;");
    if(!query.exec()){
        QMessageBox::warning(this, "Erro", "Problema no SELECT * FROM produto");
    }else{
        ui->tabelaProdutos->setColumnCount(4);
        ui->tabelaProdutos->setRowCount(0);
        while(query.next()){
            ui->tabelaProdutos->insertRow(cont);
            ui->tabelaProdutos->setRowHeight(cont, 23);
            ui->tabelaProdutos->setItem(cont, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tabelaProdutos->setItem(cont, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tabelaProdutos->setItem(cont, 2, new QTableWidgetItem(query.value(3).toString()));
            ui->tabelaProdutos->setItem(cont, 3, new QTableWidgetItem(query.value(4).toString()));
            cont++;
        }
        formataTabela();
    }

}

void CrudProdutoWindow::formataTabela()
{
    QStringList nomeColunas = {"ID", "Nome", "Preço (R$)", "Necessita Preparo"};
    ui->tabelaProdutos->setColumnWidth(0, 50);
    ui->tabelaProdutos->setColumnWidth(1, 200);
    ui->tabelaProdutos->setColumnWidth(2, 80);
    ui->tabelaProdutos->setColumnWidth(3, 120);
    ui->tabelaProdutos->setHorizontalHeaderLabels(nomeColunas);
    ui->tabelaProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabelaProdutos->setSortingEnabled(false);
    ui->tabelaProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);

}

void CrudProdutoWindow::on_pushButtonNovoProduto_clicked()
{
    NovoProdutoWindow *npw = new NovoProdutoWindow;
    npw->setModal(true);
    npw->exec();
    preencheTabela();
}

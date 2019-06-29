#include "crudusuariowindow.h"
#include "ui_crudusuariowindow.h"
#include "mainwindow.h"
#include "novousuariowindow.h"

crudusuariowindow::crudusuariowindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crudusuariowindow)
{
    ui->setupUi(this);
}

crudusuariowindow::~crudusuariowindow()
{
    delete ui;
}

void crudusuariowindow::preencheTabela()
{
    QSqlQuery query;
    int cont = 0;
    query.prepare("SELECT * FROM usuario;");
    if(!query.exec()){
        QMessageBox::warning(this, "Erro", "Problema no SELECT * FROM usuario");
    }else{
        ui->tabelaUsuarios->setColumnCount(4);
        ui->tabelaUsuarios->setRowCount(0);
        while(query.next()){
            ui->tabelaUsuarios->insertRow(cont);
            ui->tabelaUsuarios->setRowHeight(cont, 23);
            ui->tabelaUsuarios->setItem(cont, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tabelaUsuarios->setItem(cont, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tabelaUsuarios->setItem(cont, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tabelaUsuarios->setItem(cont, 3, new QTableWidgetItem(query.value(4).toString()));
            cont++;
        }
        formataTabela();
    }
}

void crudusuariowindow::formataTabela()
{
    QStringList nomeColunas = {"ID", "Nome", "Login", "Tipo"};
    ui->tabelaUsuarios->setColumnWidth(0, 50);
    ui->tabelaUsuarios->setColumnWidth(1, 100);
    ui->tabelaUsuarios->setColumnWidth(2, 80);
    ui->tabelaUsuarios->setColumnWidth(3, 50);
    ui->tabelaUsuarios->setHorizontalHeaderLabels(nomeColunas);
    ui->tabelaUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabelaUsuarios->setSortingEnabled(false);
    ui->tabelaUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void crudusuariowindow::on_pushButtonNovoUsuario_clicked()
{
    NovoUsuarioWindow *nuw = new NovoUsuarioWindow;
    nuw->setModal(true);
    nuw->exec();
    preencheTabela();
}

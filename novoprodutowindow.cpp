#include "novoprodutowindow.h"
#include "ui_novoprodutowindow.h"

NovoProdutoWindow::NovoProdutoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoProdutoWindow)
{
    ui->setupUi(this);
}

NovoProdutoWindow::~NovoProdutoWindow()
{
    delete ui;
}

void NovoProdutoWindow::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString booleano = ui->necessitaPreparoCheckBox->isChecked() ? "true" : "false";
    query.prepare("INSERT INTO produto(nome, descricao, preco, necessita_preparo) VALUES(:nome, :descricao, :preco, :necessita_preparo);");
    query.bindValue(":nome", ui->nomeLineEdit->text());
    query.bindValue(":descricao", ui->descricaoLineEdit->text());
    query.bindValue(":preco", ui->precoLineEdit->text());
    query.bindValue(":necessita_preparo", booleano);
    if(ui->nomeLineEdit->text() == "" || ui->precoLineEdit->text() == ""){
        QMessageBox::warning(this, "Aviso!", "Nome e Preço são obrigatórios!");
        return;
    }
    if(!query.exec())
        QMessageBox::warning(this, "Aviso!", "Query de INSERT INTO produto não foi executada!");
}

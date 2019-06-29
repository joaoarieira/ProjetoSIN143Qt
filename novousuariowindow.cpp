#include "novousuariowindow.h"
#include "ui_novousuariowindow.h"
#include "mainwindow.h"

NovoUsuarioWindow::NovoUsuarioWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoUsuarioWindow)
{
    ui->setupUi(this);
}

NovoUsuarioWindow::~NovoUsuarioWindow()
{
    delete ui;
}

void NovoUsuarioWindow::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString nova_senha_md5;
    QString novo_tipo = ui->administradorCheckBox->isChecked() ? "1" : "2";

    if(ui->senhaLineEdit->text() == ui->repetirSenhaLineEdit->text())
        nova_senha_md5 = ui->senhaLineEdit->text();
    else
        QMessageBox::warning(this, "Aviso!", "As senhas não são iguais!");
    nova_senha_md5 = QString::fromStdString(md5(nova_senha_md5.toStdString()));

    query.prepare("INSERT INTO usuario(nome, login, senha_md5, tipo) VALUES(:nome, :login, :senha_md5, :tipo);");
    query.bindValue(":nome", ui->nomeLineEdit->text());
    query.bindValue(":login", ui->loginLineEdit->text());
    query.bindValue(":senha_md5", nova_senha_md5);
    query.bindValue(":tipo", novo_tipo);
    if(ui->nomeLineEdit->text() == "" || ui->loginLabel->text() == "" || ui->senhaLineEdit->text() == "" || ui->repetirSenhaLineEdit->text() == ""){
        QMessageBox::warning(this, "Aviso!", "Nome, Login e Senha são obrigatórios!");
        return;
    }
    if(!query.exec())
        QMessageBox::warning(this, "Aviso!", "Query de INSERT INTO produto não foi executada!");
}

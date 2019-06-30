#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "datetimeapi.h"
#include "mainwindow.h"

static QSqlDatabase bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    bancoDeDados.setDatabaseName("C:/Users/Adelia/Documents/QtProjects/ProjetoSIN143Qt/db_sorveteria.db");
    ui->labelAvisoUsuarioSenha->hide();


    if(!bancoDeDados.open()){
        QMessageBox::warning(this,"Warning", "Não foi possível abrir o banco de dados.");
        exit(1);
    }


}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_actionC_Sorveteria_triggered()
{
    QMessageBox::about(this, "C++ Sorveteria", "SIN143 - Laboratorio de Programacao.\nIntegrantes do grupo: \nJoao\nEzequiel\nMarcel.");
}

void LoginWindow::on_actionQt_Creator_triggered()
{
    QMessageBox::aboutQt(this, "Esta é a mensagem da caixa aboutQt.");
}

void LoginWindow::on_actionSair_triggered()
{
    close();
}

void LoginWindow::on_pushButtonEntrar_clicked()
{
    if(!ui->labelAvisoUsuarioSenha->isHidden()) //esconde o aviso de usuário e senha errados
        ui->labelAvisoUsuarioSenha->hide();

    QString username = ui->lineEditUsuario->text();
    QString senha = ui->lineEditSenha->text();

    if(!bancoDeDados.isOpen()){
        qDebug() << "BD não está aberto!\n";
        exit(1);
    }

    QSqlQuery query;
    int cont = 0;

    if(query.exec("select * from usuario where login = '" + username + "' and senha_md5 = '" + QString::fromStdString(md5(senha.toStdString())) + "'")){
        while(query.next()){
            cont++;
        }
        if(cont > 0){
            MainWindow *w = new MainWindow;
            query.first();
            if(query.value(4).toInt() == 1)
                w->setCrudEnable(true);
            else
                w->setCrudEnable(false);
            this->close();
            w->show();
        }else{
            ui->labelAvisoUsuarioSenha->show();
        }
    }else{
        QMessageBox::about(this, "Mensagem", "Problema na query.");
    }
}


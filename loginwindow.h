#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "qmessagebox.h"
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include "md5.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:

    void on_actionC_Sorveteria_triggered();
    void on_actionQt_Creator_triggered();
    void on_actionSair_triggered();
    void on_pushButtonEntrar_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H

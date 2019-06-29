#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QWidget>
#include <QKeyEvent>
#include "loginwindow.h"
#include "crudprodutowindow.h"
#include "crudusuariowindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void formataTabela();

protected:
    void keyPressEvent(QKeyEvent *evento);

public slots:
    void preencheLinha();
    void preencheValorUnitario();
    void preencheValorTotal();
    void resetaQuantidade();
    void calculaTroco();
    void setCrudEnable(bool enable);

private slots:
    void on_actionSair_triggered();
    void on_actionQt_Creator_triggered();
    void on_actionSorveteria_triggered();
    void on_actionProduto_triggered();

    void on_actionUsuario_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

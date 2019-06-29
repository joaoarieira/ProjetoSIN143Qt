#ifndef CRUDPRODUTOWINDOW_H
#define CRUDPRODUTOWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "novoprodutowindow.h"

namespace Ui {
class CrudProdutoWindow;
}

class CrudProdutoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CrudProdutoWindow(QWidget *parent = nullptr);
    ~CrudProdutoWindow();
    void preencheTabela();

private slots:
    void on_pushButtonNovoProduto_clicked();
    void formataTabela();
private:
    Ui::CrudProdutoWindow *ui;
};

#endif // CRUDPRODUTOWINDOW_H

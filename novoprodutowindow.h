#ifndef NOVOPRODUTOWINDOW_H
#define NOVOPRODUTOWINDOW_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class NovoProdutoWindow;
}

class NovoProdutoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NovoProdutoWindow(QWidget *parent = nullptr);
    ~NovoProdutoWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NovoProdutoWindow *ui;
};

#endif // NOVOPRODUTOWINDOW_H

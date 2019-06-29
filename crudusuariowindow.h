#ifndef CRUDUSUARIOWINDOW_H
#define CRUDUSUARIOWINDOW_H

#include <QDialog>

namespace Ui {
class crudusuariowindow;
}

class crudusuariowindow : public QDialog
{
    Q_OBJECT

public:
    explicit crudusuariowindow(QWidget *parent = nullptr);
    ~crudusuariowindow();

public slots:
    void preencheTabela();
    void formataTabela();

private slots:
    void on_pushButtonNovoUsuario_clicked();

private:
    Ui::crudusuariowindow *ui;
};

#endif // CRUDUSUARIOWINDOW_H

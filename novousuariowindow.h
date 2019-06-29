#ifndef NOVOUSUARIOWINDOW_H
#define NOVOUSUARIOWINDOW_H

#include <QDialog>
#include "crudusuariowindow.h"

namespace Ui {
class NovoUsuarioWindow;
}

class NovoUsuarioWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NovoUsuarioWindow(QWidget *parent = nullptr);
    ~NovoUsuarioWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NovoUsuarioWindow *ui;
};

#endif // NOVOUSUARIOWINDOW_H

#ifndef FLUXOCAIXA_H
#define FLUXOCAIXA_H

#include <QMainWindow>

namespace Ui {
class FluxoCaixa;
}

class FluxoCaixa : public QMainWindow
{
    Q_OBJECT

public:
    explicit FluxoCaixa(QWidget *parent = nullptr);
    ~FluxoCaixa();

private:
    Ui::FluxoCaixa *ui;
};

#endif // FLUXOCAIXA_H

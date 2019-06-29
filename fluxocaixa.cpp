#include "fluxocaixa.h"
#include "ui_fluxocaixa.h"

FluxoCaixa::FluxoCaixa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FluxoCaixa)
{
    ui->setupUi(this);
}

FluxoCaixa::~FluxoCaixa()
{
    delete ui;
}

#include "batchlist.h"
#include "ui_batchlist.h"

BatchList::BatchList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchList)
{
    ui->setupUi(this);
}

BatchList::~BatchList()
{
    delete ui;
}

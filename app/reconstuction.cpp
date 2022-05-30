#include "reconstuction.h"
#include "ui_reconstuction.h"

Reconstuction::Reconstuction(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Reconstuction)
{
  ui->setupUi(this);
}

Reconstuction::~Reconstuction()
{
  delete ui;
}

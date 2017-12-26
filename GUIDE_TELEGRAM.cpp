#include "GUIDE_TELEGRAM.h"
#include "ui_GUIDE_TELEGRAM.h"

GUIDE_TELEGRAM::GUIDE_TELEGRAM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIDE_TELEGRAM)
{
    ui->setupUi(this);
}

GUIDE_TELEGRAM::~GUIDE_TELEGRAM()
{
    delete ui;
}

#include "GUIDE_MAIN.h"
#include "ui_GUIDE_MAIN.h"

GUIDE_MAIN::GUIDE_MAIN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIDE_MAIN)
{
    ui->setupUi(this);
}

GUIDE_MAIN::~GUIDE_MAIN()
{
    delete ui;
}

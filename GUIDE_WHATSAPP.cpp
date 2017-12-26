#include "GUIDE_WHATSAPP.h"
#include "ui_GUIDE_WHATSAPP.h"

GUIDE_WHATSAPP::GUIDE_WHATSAPP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIDE_WHATSAPP)
{
    ui->setupUi(this);
}

GUIDE_WHATSAPP::~GUIDE_WHATSAPP()
{
    delete ui;
}

#include "GUIDE_WECHAT.h"
#include "ui_GUIDE_WECHAT.h"

GUIDE_WECHAT::GUIDE_WECHAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUIDE_WECHAT)
{
    ui->setupUi(this);
}

GUIDE_WECHAT::~GUIDE_WECHAT()
{
    delete ui;
}

#include "instruction.h"
#include "ui_instruction.h"

Instruction::Instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);
    ui->textBrowser->setVisible(false);
}

Instruction::~Instruction()
{
    delete ui;
}

void Instruction::setUrl(const QString & url) {

    ui->installUrllineEdit->setText(url);
}

#ifndef GUIDE_WHATSAPP_H
#define GUIDE_WHATSAPP_H

#include <QWidget>

namespace Ui {
class GUIDE_WHATSAPP;
}

class GUIDE_WHATSAPP : public QWidget
{
    Q_OBJECT

public:
    explicit GUIDE_WHATSAPP(QWidget *parent = 0);
    ~GUIDE_WHATSAPP();

private:
    Ui::GUIDE_WHATSAPP *ui;
};

#endif // GUIDE_WHATSAPP_H

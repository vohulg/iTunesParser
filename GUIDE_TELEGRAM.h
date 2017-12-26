#ifndef GUIDE_TELEGRAM_H
#define GUIDE_TELEGRAM_H

#include <QWidget>

namespace Ui {
class GUIDE_TELEGRAM;
}

class GUIDE_TELEGRAM : public QWidget
{
    Q_OBJECT

public:
    explicit GUIDE_TELEGRAM(QWidget *parent = 0);
    ~GUIDE_TELEGRAM();

private:
    Ui::GUIDE_TELEGRAM *ui;
};

#endif // GUIDE_TELEGRAM_H

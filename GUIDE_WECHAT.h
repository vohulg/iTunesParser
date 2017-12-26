#ifndef GUIDE_WECHAT_H
#define GUIDE_WECHAT_H

#include <QWidget>

namespace Ui {
class GUIDE_WECHAT;
}

class GUIDE_WECHAT : public QWidget
{
    Q_OBJECT

public:
    explicit GUIDE_WECHAT(QWidget *parent = 0);
    ~GUIDE_WECHAT();

private:
    Ui::GUIDE_WECHAT *ui;
};

#endif // GUIDE_WECHAT_H

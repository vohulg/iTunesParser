#ifndef GUIDE_MAIN_H
#define GUIDE_MAIN_H

#include <QWidget>

namespace Ui {
class GUIDE_MAIN;
}

class GUIDE_MAIN : public QWidget
{
    Q_OBJECT

public:
    explicit GUIDE_MAIN(QWidget *parent = 0);
    ~GUIDE_MAIN();

private:
    Ui::GUIDE_MAIN *ui;
};

#endif // GUIDE_MAIN_H

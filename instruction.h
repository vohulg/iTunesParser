#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>

namespace Ui {
class Instruction;
}

class Instruction : public QWidget
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = 0);
    ~Instruction();

    QString setUrl(const QString & url);

private:
    Ui::Instruction *ui;
};

#endif // INSTRUCTION_H

#ifndef LEC09_H
#define LEC09_H

#include <QFrame>

namespace Ui {
    class lec09;
}

class lec09 : public QFrame
{
    Q_OBJECT

public:
    explicit lec09(QWidget *parent = 0);
    ~lec09();

private:
    Ui::lec09 *ui;
};

#endif // LEC09_H

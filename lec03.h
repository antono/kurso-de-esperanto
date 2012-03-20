#ifndef LEC03_H
#define LEC03_H

#include <QFrame>

namespace Ui {
    class lec03;
}

class lec03 : public QFrame
{
    Q_OBJECT

public:
    explicit lec03(QWidget *parent = 0);
    ~lec03();

private:
    Ui::lec03 *ui;
};

#endif // LEC03_H

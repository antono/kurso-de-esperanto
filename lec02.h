#ifndef LEC02_H
#define LEC02_H

#include <QFrame>
#include <indikilo.h>

namespace Ui {
    class lec02;
}

class lec02 : public QFrame
{
    Q_OBJECT

public:
    explicit lec02(QWidget *parent = 0);
    ~lec02();


private:
    Ui::lec02 *ui;


};

#endif // LEC02_H

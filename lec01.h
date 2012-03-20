#ifndef LEC01_H
#define LEC01_H

#include <QFrame>
#include <indikilo.h>

namespace Ui {
    class lec01;
}

class lec01 : public QFrame
{
    Q_OBJECT

public:
    explicit lec01(QWidget *parent = 0);
    ~lec01();


private:
    Ui::lec01 *ui;


};

#endif // LEC01_H

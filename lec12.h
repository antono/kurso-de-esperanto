#ifndef LEC12_H
#define LEC12_H

#include <QFrame>
#include "indikilo.h"

namespace Ui {
    class lec12;
}

class lec12 : public QFrame
{
    Q_OBJECT

public:
    explicit lec12(QWidget *parent = 0);
    ~lec12();


private:
    Ui::lec12 *ui;

};

#endif // LEC12_H

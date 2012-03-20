#ifndef LEC10_H
#define LEC10_H

#include <QFrame>

namespace Ui {
    class lec10;
}

class lec10 : public QFrame
{
    Q_OBJECT

public:
    explicit lec10(QWidget *parent = 0);
    ~lec10();

private:
    Ui::lec10 *ui;
};

#endif // LEC10_H

#ifndef LEC11_H
#define LEC11_H

#include <QFrame>

namespace Ui {
    class lec11;
}

class lec11 : public QFrame
{
    Q_OBJECT

public:
    explicit lec11(QWidget *parent = 0);
    ~lec11();

private:
    Ui::lec11 *ui;
};

#endif // LEC11_H

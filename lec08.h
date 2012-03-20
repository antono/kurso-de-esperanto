#ifndef LEC08_H
#define LEC08_H

#include <QFrame>

namespace Ui {
    class lec08;
}

class lec08 : public QFrame
{
    Q_OBJECT

public:
    explicit lec08(QWidget *parent = 0);
    ~lec08();

private:
    Ui::lec08 *ui;
};

#endif // LEC08_H

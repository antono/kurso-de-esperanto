#ifndef LEC04_H
#define LEC04_H

#include <QFrame>

namespace Ui {
    class lec04;
}

class lec04 : public QFrame
{
    Q_OBJECT

public:
    explicit lec04(QWidget *parent = 0);
    ~lec04();

private:
    Ui::lec04 *ui;
};

#endif // LEC04_H

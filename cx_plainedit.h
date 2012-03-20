#ifndef CX_PLAINEDIT_H
#define CX_PLAINEDIT_H

#include <QPlainTextEdit>
#include <QKeyEvent>

extern bool lCxapeligo;


class cx_plainedit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit cx_plainedit(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *);

signals:

public slots:

};

#endif // CX_PLAINEDIT_H

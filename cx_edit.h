#ifndef CX_EDIT_H
#define CX_EDIT_H

#include <QLineEdit>
#include <QKeyEvent>

extern bool lCxapeligo;

class cx_edit : public QLineEdit
{
    Q_OBJECT
public:
    explicit cx_edit(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *);

signals:

public slots:

};

#endif // CX_EDIT_H

#ifndef KLAKBUTONO_H
#define KLAKBUTONO_H

#include <QPushButton>

class klakbutono : public QPushButton
{
    Q_OBJECT
public:
    explicit klakbutono(QWidget *parent = 0);


signals:


public slots:

private slots:
    void klakita(bool checked);

};

#endif // KLAKBUTONO_H

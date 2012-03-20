#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

signals:
        void clicked();

public slots:
        void slotClicked();

protected:
        void mouseReleaseEvent ( QMouseEvent * event ) ;

};

#endif // MYLABEL_H

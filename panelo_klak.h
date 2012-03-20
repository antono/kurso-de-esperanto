#ifndef PANELO_KLAK_H
#define PANELO_KLAK_H

#include <QFrame>

class panelo_klak : public QFrame
{
    Q_OBJECT
public:
    explicit panelo_klak(QWidget *parent = 0);
    
signals:
        void clicked();

protected:
        void mouseReleaseEvent ( QMouseEvent * event ) ;

    
};

#endif // PANELO_KLAK_H

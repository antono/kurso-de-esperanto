#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>

class clicklabel : public QLabel
{
    Q_OBJECT
public:
    //explicit clicklabel(QObject *parent = 0);
    clicklabel( const QString & text, QWidget * parent = 0 );
    ~clicklabel(){}

signals:
    void clicked();

public slots:
    void slotClicked();

protected:
        void mouseReleaseEvent ( QMouseEvent * event ) ;

};

#endif // CLICKLABEL_H


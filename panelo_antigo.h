#ifndef PANELO_H
#define PANELO_H

#include <QFrame>
#include <QTableWidget>
#include <QStringList>
#include <indikilo.h>
#include <label_klakebla.h>
#include <panelo_klak.h>

class panelo : public QFrame
{
    Q_OBJECT
public:
    explicit panelo(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QString leciono;
    QTabWidget *pagharo;
    QStringList nomoj;
    QList<indikilo *> chiuj_indikiloj;
    QList<label_klakebla *> chiuj_label;
    QList<panelo_klak *> chiuj_paneloj;

    
};

#endif // PANELO_H

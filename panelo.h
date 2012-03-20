#ifndef PANELO_H
#define PANELO_H

#include <QFrame>
#include <QTabWidget>
#include <QStringList>
#include <indikilo.h>
#include <label_klakebla.h>
#include <panelo_klak.h>


namespace Ui {
class panelo;
}

class panelo : public QFrame
{
    Q_OBJECT
    
public:
    explicit panelo(QWidget *parent = 0);
    ~panelo();
    
private slots:
    void purigas();

    void klakas();

    void montras_sagon(int);

private:
    Ui::panelo *ui;

    QString leciono;
    QTabWidget *pagharo;
    QList<QTabWidget *> chiuj_tab;
    QList<indikilo *> chiuj_indikiloj;
};

#endif // PANELO_H

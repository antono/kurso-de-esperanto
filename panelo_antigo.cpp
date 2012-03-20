#include "panelo.h"
#include "panelo_klak.h"
#include <QSettings>

panelo::panelo(QWidget *parent) :
    QFrame(parent)
{
    QList<QTabWidget *> chiuj_tab = this->parent()->findChildren<QTabWidget *>();
    chiuj_indikiloj = this->findChildren<indikilo *>();
    chiuj_label = this->findChildren<label_klakebla *>();
    chiuj_paneloj = this->findChildren<panelo_klak *>();
    int i;
    for (i = 0; i < chiuj_paneloj.count(); i++ )
    {
        chiuj_paneloj.at(i)->setVisible(false);
    }

    pagharo = chiuj_tab.at(0);
    leciono = pagharo->objectName().left(5);
    QSettings menuo(":ekzercoj/menuo.ini", QSettings::IniFormat);
    menuo.beginGroup(leciono);
    QString nomo, nomo2;
    for (i = 0; i < pagharo->count(); i++)
    {
        nomo = menuo.value(QString::number(i)).toString();
        nomo2 = (nomo.left(3) == "Ekz" ?  "Lec00" : leciono) + "_Pan00_" + nomo;
        chiuj_label.at(i)->setObjectName(nomo2);
        chiuj_paneloj.at(i)->setVisible(true);

    }
    menuo.endGroup();


}

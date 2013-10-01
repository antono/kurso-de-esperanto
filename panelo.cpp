/*
    Kurso de Esperanto - a free multimedia course to teach yourself the
    international language.
    Copyright (C) 2000-2012 Carlos Alberto Alves Pereira
    karlo@kurso.com.br

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Kurso de Esperanto - multrimeda komputila kurso por memlernado de
    la internacia lingvo.
    Kopirajto (C) 2000-2012 Carlos Alberto Alves Pereira
    karlo@kurso.com.br

    Tiu ĉi programo estas libera softvaro: vi povas ĝin redisdoni aŭ
    ĝin modifi laŭ la kondiĉoj de GNU-a Ĝenerala Publika Uzpermeso versio 3
    kiel publikigita de Free Software Foundation.

    Tiu ĉi programo estas disdonita kun la espero, ke ĝi estos utila,
    sed sen ia garantio; eĉ sen la implica garantio de komercebleco aŭ
    taŭgeco por specifa celo. Vidu la GNU-an Ĝeneralan Publikan Uzpermeson
    por pliaj detaloj.

    Vi devus esti ricevinta kopion de la GNU-a Ĝenerala Publika Uzpermeso
    kune kun ĉi tiu programo. Se ne, iru al <http://www.gnu.org/licenses/>.
*/

#include "panelo.h"
#include "ui_panelo.h"
#include <QSettings>
#include <QDebug>
#include "panelo_bildo.h"

panelo::panelo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::panelo)
{
    ui->setupUi(this);

    chiuj_indikiloj = this->findChildren<indikilo *>();
    QList<label_klakebla *> chiuj_label = this->findChildren<label_klakebla *>();
    QList<panelo_klak *> chiuj_paneloj = this->findChildren<panelo_klak *>();
    QList<dividilo *> chiuj_dividiloj = this->findChildren<dividilo *>();
    QList<panelo_bildo *> chiuj_bildoj = this->findChildren<panelo_bildo *>();
    leciono = "Lec" + this->parentWidget()->objectName().right(2);

    //QPixmap titolo(":paneloj/leciono" + leciono.right(2) + ".png");
    //this->ui->titolo_leciono->setPixmap(titolo);

    int i;
    for (i = 0; i < chiuj_paneloj.count(); i++ )
    {
        chiuj_paneloj.at(i)->setVisible(false);
        chiuj_dividiloj.at(i)->setVisible(false);
    }

    QSettings menuo(":ekzercoj/menuo.ini", QSettings::IniFormat);
    menuo.beginGroup(leciono);
    QStringList chiuj = menuo.allKeys();
    QString nomo, nomo2;
    for (i = 0; i < chiuj.count(); i++)
    {
        nomo = menuo.value(QString::number(i)).toString();

        if (nomo != "ripetata")
            nomo2 = (nomo.left(3) == "Ekz" ?  "Lec00" : leciono) + "_Pan00_" + nomo;
        else
        {
            nomo2 = "ripetata" + QString::number(i);
            chiuj_label.at(i)->setText(QString::fromUtf8("   \u201D   \u201D   \u201D"));
        }

        chiuj_label.at(i)->setObjectName(nomo2);
        chiuj_paneloj.at(i)->setProperty("pagho", i);
        chiuj_paneloj.at(i)->setVisible(true);
        chiuj_dividiloj.at(i)->setVisible(true);

    }
    menuo.endGroup();

    menuo.beginGroup(leciono + "_tipo");
    chiuj = menuo.allKeys();
    for (i = 0; i < chiuj.count(); i++)
    {
        nomo = menuo.value(QString::number(i)).toString();

        if (nomo == "sendas")
        {
            QPixmap bildo(":paneloj/sendas.png");
            chiuj_bildoj.at(i)->setPixmap(bildo);
        }
        else
            chiuj_bildoj.at(i)->setVisible(false);
    }
    menuo.endGroup();

    purigas();
    chiuj_indikiloj[0]->setVisible(true);

}

panelo::~panelo()
{
    delete ui;
}


void panelo::purigas()
{
    for (int i = 0; i < chiuj_indikiloj.count(); i++)
        chiuj_indikiloj[i]->setVisible(false);
}


void panelo::klakas()
{
    chiuj_tab = this->parentWidget()->findChildren<QTabWidget *>();
    pagharo = chiuj_tab.at(0);

    int pagho;
    panelo_klak * klakita = qobject_cast<panelo_klak *>(QObject::sender());

    if (klakita > 0)
        pagho = klakita->property("pagho").toInt();
    else
        pagho = 0;

    pagharo->setCurrentIndex(pagho);

}

void panelo::montras_sagon(int pagho)
{
    this->setUpdatesEnabled(false);
    purigas();
    if (chiuj_indikiloj.count() >= pagho)
        chiuj_indikiloj[pagho]->setVisible(true);
    this->setUpdatesEnabled(true);
}


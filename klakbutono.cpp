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

#include "klakbutono.h"
#include "funkcioj.h"
#include <QPixmap>
#include <QBitmap>

klakbutono::klakbutono(QWidget *parent) :
    QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked(bool)),
            this, SLOT(klakita(bool)));
    //QPixmap kursoro_n(":ikonoj/kursoro_prononco.png");
    //kursoro_n.setMask(QBitmap(":ikonoj/kursoro_prononco.png"));
    //this->setCursor(kursoro_n);
    this->setFlat(true);

}

void klakbutono::klakita(bool checked)
{
    QString sTeksto = this->text(), sDosiero, Nomo;
    Nomo = this->objectName();

    sTeksto = sTeksto.replace(QString::fromUtf8("\u200E"), "");

    QString cxTeksto = CxSist(sTeksto,1);
    QString SonLeciono = this->objectName().mid(3,2);
    QString Vojo = "sonoj/lec" + SonLeciono + "/";
    bool lEstasNumero = true;
    if (cxTeksto.size() < 9)
        if (cxTeksto.indexOf(" ") < 0  && cxTeksto.indexOf("!") < 0)
            lEstasNumero = false;

    if (lEstasNumero)
    {
        sDosiero = Vojo + "btn" + this->objectName().mid(12) + mp3_finajho;
    }
    else
    {
        if (cxTeksto == "aux")
            cxTeksto == "auh";
        sDosiero = Vojo + cxTeksto + mp3_finajho;
    }

    mp3(sDosiero);

}

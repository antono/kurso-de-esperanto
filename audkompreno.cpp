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

#include "audkompreno.h"
#include "ui_audkompreno.h"
#include "funkcioj.h"
#include <QPushButton>
#include <QTime>

audkompreno::audkompreno(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::audkompreno)
{
    ui->setupUi(this);
    LTR_Marko = QString::fromUtf8("\u200E");

}


audkompreno::~audkompreno()
{
    delete ui;
}

void audkompreno::on_BitBtn8_clicked()
{

    chiuj_label = this->ui->vortujo->findChildren<QLabel *>();
    EkzercoAudado = this->objectName().right(4);
    Leciono = this->objectName().left(5);
    iEk02D = _Matriz(&aEk02D, EkzercoAudado, "D");
    this->ui->BitBtn8->setEnabled(false);
    this->ui->BitBtn9->setEnabled(true);
    this->ui->BitBtn10->setEnabled(true);
    this->ui->Edit1->setEnabled(true);

    if (iEk02D > 48)
        this->ui->Placar1->setValue(48);
    else
        this->ui->Placar1->setValue(iEk02D);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj2 = 0;
    iEraraj2 = 0;
    //aEk02A.clear(iEk02D);
    aEk02A.clear();

    int i;
    for ( i = 0; i < 48; i++)
    {
        chiuj_label[i]->setText("          ");
        //aEk02A[i] = false;
    }

    for ( i = 0; i < iEk02D; i++)
    {
        //aEk02A[i] = false;
        aEk02A << false;
    }
    novavorto();

}

void audkompreno::novavorto()
{
    QString sTeksto = "";
    iAleat2 = random(iEk02D);
    while (aEk02A[iAleat2])
        iAleat2 = random(iEk02D);
    if (aEk02D[iAleat2].toInt() > 0)
    {
        chiuj_butonoj =
                this->parentWidget()->parentWidget()->parentWidget()->findChildren<QPushButton *>(Leciono + "_Button"  + aEk02D[iAleat2]);
        if (chiuj_butonoj.count() > 0)
            sTeksto = chiuj_butonoj[0]->text().remove(LTR_Marko);
        else
            sTeksto = "";

        sMp3dos = "sonoj/lec" + EkzercoAudado.left(2) + "/btn" + aEk02D[iAleat2] + mp3_finajho;
    }
    else
    {
        sTeksto = CxSist(aEk02D[iAleat2],1);
        if (sTeksto == "aux")
            sTeksto = "auh";
        sMp3dos = "sonoj/lec" + EkzercoAudado.left(2) + "/" + sTeksto + mp3_finajho;
    }
    mp3(sMp3dos);

    this->ui->Edit1->setText("");

    this->ui->Edit1->setFocus();
}

void audkompreno::on_BitBtn10_clicked()
{
    this->ui->BitBtn8->setEnabled(true);
    this->ui->BitBtn9->setEnabled(false);
    this->ui->BitBtn10->setEnabled(false);
    this->ui->Edit1->setText("");
    this->ui->Edit1->setEnabled(false);
    this->ui->BitBtn8->setFocus();

}

void audkompreno::on_BitBtn9_clicked()
{
    mp3(sMp3dos);
    this->ui->Edit1->setFocus();
}

void audkompreno::analizu()
{
    QString sTeksto, sTesto;
    sTeksto = this->ui->Edit1->text();
    if (sTeksto != "")
    {
        if (aEk02D[iAleat2].toInt() > 0)
        {
            QList<QPushButton *> chiuj_butonoj =
                    this->parentWidget()->parentWidget()->parentWidget()->findChildren<QPushButton *>(Leciono + "_Button" + aEk02D[iAleat2]);
            if (chiuj_butonoj.count() > 0)
                sTesto = chiuj_butonoj[0]->text().remove(LTR_Marko);
            else
                sTesto = "";
        }
        else
            sTesto = aEk02D[iAleat2];
        sTeksto = purigas(sTeksto, true);
        sTesto  = purigas(sTesto, true);

        if (sTesto == sTeksto)
        {
            // Noteto(true);
            iKorektaj2++;
            this->ui->Placar2->setValue(iKorektaj2);
            if (iEk02D > 48)
                this->ui->Placar1->setValue(48 - iKorektaj2);
            else
                this->ui->Placar1->setValue(iEk02D - iKorektaj2);
            aEk02A[iAleat2] = true;
            chiuj_label[iKorektaj2 - 1]->setText(sTeksto);
            Sinkronigu();
        }
        else
        {
            Noteto(false);
            iEraraj2++;
            this->ui->Placar3->setValue(iEraraj2);
            this->ui->BitBtn9->setEnabled(false);
            this->ui->BitBtn10->setEnabled(false);
            this->ui->Edit1->setEnabled(false);
            this->ui->Korekta->setText(sTesto);

            tekstoblinko(this->ui->Korekta);

            this->ui->BitBtn9->setEnabled(true);
            this->ui->BitBtn10->setEnabled(true);
            this->ui->Edit1->setEnabled(true);
            this->ui->Korekta->setText("");
        }
        this->ui->Placar4->setValue((iKorektaj2 * 100) / (iEraraj2 + iKorektaj2));
        if ((iKorektaj2 < iEk02D) && (iKorektaj2 < 48))
            novavorto();
        else
        {
            Mesagxo(iEraraj2, iKorektaj2);
            on_BitBtn10_clicked();
        }
    }
}

void audkompreno::on_Edit1_returnPressed()
{
    analizu();
}

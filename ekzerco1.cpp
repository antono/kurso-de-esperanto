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

#include "ekzerco1.h"
#include "ui_ekzerco1.h"
#include "funkcioj.h"
#include <QTime>



ekzerco1::ekzerco1(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ekzerco1)
{
    ui->setupUi(this);
}

ekzerco1::~ekzerco1()
{
    delete ui;
}

void ekzerco1::on_BitBtn1_clicked()
{
    chiuj_butonoj = this->ui->butonujo->findChildren<QPushButton *>();
    iEk01D = _Matriz(&aEk01D, "0101", "D");
    this->ui->BitBtn1->setEnabled(false);
    this->ui->BitBtn2->setEnabled(true);
    this->ui->Placar1->setValue((iEk01D / 4) * 4);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj = 0;
    iEraraj = 0;
    //bool aEk01A[iEk01D];
    //aEk01A.clear(iEk01D);
    aEk01A.clear();
    for (int i = 0; i < iEk01D; i++)
        //aEk01A[i] = false;
        aEk01A << false;
    //randomize();
    novafrazo();
}

void ekzerco1::novafrazo()
{
    int i, j, k, iAleat2, iAleat3;
    for (i=0; i < 4; i++)
    {
        if (this->ui->Placar1->value() > 11)
        {
            iAleat1 = random(iEk01D);
            while (aEk01A[iAleat1])
                iAleat1 = random(iEk01D);
        }
        else
        {
            iAleat1 = 0;
            while (aEk01A[iAleat1])
                iAleat1++;
        }
        aEk01A[iAleat1] = true;
        Selektitaj[i] = iAleat1;

    }

    for (i=0; i < 2; i++)
    {
        iAleat2 = random(iEk01D);
        for (j=0; j < 4; j++)
        {
            while (iAleat2 == Selektitaj[j])
                iAleat2 = random(iEk01D);
        }
        Hazardaj[i] = iAleat2;
    }

    j = 0;
    k = 0;
    i = 0;
    do
    {
        chiuj_butonoj[i]->setEnabled(true);
        iAleat3 = random(3);
        if ( (iAleat3 == 0) && (j < 2))
        {
            chiuj_butonoj[i]->setText(aEk01D[Hazardaj[j]]);
            j++;
            i++;
        }
        else
        {
            if (k < 4)
            {
                chiuj_butonoj[i]->setText(aEk01D[Selektitaj[k]]);
                PozicioSelektitaj[k] = i;
                k++;
                i++;
            }
        }
     } while ( i < 6 );

    for (i = 0; i < 6; i++)
        aFrazoElek[i] = false;
    lNovaFrazo = true;
    novavorto();

}

void ekzerco1::novavorto()
{
    iAleat1 = random(4);
    while (aFrazoElek[iAleat1])
        iAleat1 = random(4);
    QString sTeksto = CxSist( aEk01D[Selektitaj[iAleat1]], 1);
    if (sTeksto == "aux")
        sTeksto = "auh";
    sMp3dos = "sonoj/lec01/" +  sTeksto + mp3_finajho;

    mp3(sMp3dos);

    this->ui->BitBtn3->setEnabled(true);

    this->ui->butonujo->setFocus();
    JamKlakis = false;

}


void ekzerco1::on_BitBtn3_clicked()
{
    mp3(sMp3dos);
}

void ekzerco1::on_BitBtn2_clicked()
{
    this->ui->BitBtn1->setEnabled(true);
    this->ui->BitBtn2->setEnabled(false);
    this->ui->BitBtn3->setEnabled(false);

    for (int i = 0; i < 6; i++)
        chiuj_butonoj[i]->setEnabled(false);
    this->ui->BitBtn1->setFocus();    
}

void ekzerco1::vortoklako(int klakita)
{
    QString sTeste1, sTeste2;
    if (!JamKlakis)
    {
        sTeste1 = chiuj_butonoj[klakita]->text();
        sTeste2 = aEk01D[Selektitaj[iAleat1]];
        if ( sTeste1 == sTeste2)
        {
            iKorektaj++;
            this->ui->Placar2->setValue(iKorektaj);
            this->ui->Placar1->setValue(((iEk01D /4)*4) - iKorektaj);
            aFrazoElek[iAleat1] = true;
            chiuj_butonoj[klakita]->setEnabled(false);
            lNovaFrazo = false;
        }
        else
        {
            JamKlakis = true;
            this->ui->BitBtn3->setEnabled(false);
            Ne();
            iEraraj++;
            this->ui->Placar3->setValue(iEraraj);
            this->ui->BitBtn3->setEnabled(false);
            this->ui->butonujo->setEnabled(false);

            tekstoblinko(chiuj_butonoj.at(PozicioSelektitaj[iAleat1]));

            this->ui->BitBtn3->setEnabled(true);
            this->ui->butonujo->setEnabled(true);
            JamKlakis = false;
        }

        this->ui->Placar4->setValue((iKorektaj * 100)/ (iEraraj+iKorektaj));
        if (iKorektaj < ((iEk01D/4)*4))
        {
            if ((((iKorektaj % 4) == 0)) && (!lNovaFrazo))
                novafrazo();
            else
                novavorto();
        }
        else
        {
            Mesagxo(iEraraj,iKorektaj);
            on_BitBtn2_clicked();
        }

    }
}

void ekzerco1::on_butono0_clicked()
{
    vortoklako(0);
}

void ekzerco1::on_butono1_clicked()
{
    vortoklako(2);
}

void ekzerco1::on_butono2_clicked()
{
    vortoklako(4);
}

void ekzerco1::on_butono3_clicked()
{
    vortoklako(1);
}

void ekzerco1::on_butono4_clicked()
{
    vortoklako(3);
}

void ekzerco1::on_butono5_clicked()
{
    vortoklako(5);
}

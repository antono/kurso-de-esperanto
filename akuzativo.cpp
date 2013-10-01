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

#include "akuzativo.h"
#include "ui_akuzativo.h"
#include "funkcioj.h"
#include <QLabel>
#include <QBitmap>
#include <QtCore>
#include <QTime>



akuzativo::akuzativo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::akuzativo)
{
    ui->setupUi(this);
    QPixmap kursoro_n(":ikonoj/kursoro_n.png");
    kursoro_n.setMask(QBitmap(":ikonoj/kursoro_n_masko.png"));
    chiuj_label = this->ui->Vortoj->findChildren<QLabel *>();
    for (int i = 0; i < chiuj_label.count(); i++)
        chiuj_label[i]->setCursor(kursoro_n);
}

akuzativo::~akuzativo()
{
    delete ui;
}

void akuzativo::on_BitBtn1_clicked()
{
    QString EkzercoAkuzativo = this->objectName().right(4);

    iEk02D = _Matriz2(&aEk02D,EkzercoAkuzativo,"D", 11);
    _Matriz2(&aEk02R,EkzercoAkuzativo,"R",11);
    _Matriz2(&aEk02K, EkzercoAkuzativo, "K", 11);
    _Matriz(&aEk02T, EkzercoAkuzativoTrad,"T");
    while (aEk02T.size() < iEk02D)
        aEk02T.append("");

    _Matriz(&Klarigoj, "Klarigoj", "T");

    while (Klarigoj.size() < 13)
        Klarigoj.append("");

    this->ui->BitBtn1->setEnabled(false);
    this->ui->BitBtn3->setEnabled(true);
    this->ui->Placar1->setValue(iEk02D);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj = 0;
    iEraraj = 0;
    //aEk02A.clear(iEk02D);

    aEk02A.clear();
    for (int i = 0; i < iEk02D; i++)
        //aEk02A[i] = false;
        aEk02A << false;
    novafrazo();
    this->ui->Vortoj->setEnabled(true);

    this->ui->BitBtn2->setEnabled(true);
    this->ui->BitBtn2->setFocus();
}

void akuzativo::on_BitBtn3_clicked()
{
    this->ui->BitBtn1->setEnabled(true);
    this->ui->BitBtn2->setEnabled(false);
    this->ui->BitBtn3->setEnabled(false);
    this->ui->Vortoj->setEnabled(false);
    this->ui->Traduko1->setText("");
    this->ui->Klarigo->setText("");
    for (int i = 0; i < chiuj_label.count(); i++)
        chiuj_label[i]->setText("");
    this->ui->BitBtn1->setFocus();

}


void akuzativo::novafrazo()
{
    int j, i, iVortoj;
    for (j = 0; j < 11; j++)
        aFrazoElek[j] = "";
    iAleat2 = random(iEk02D);
    while (aEk02A[iAleat2])
        iAleat2 = random(iEk02D);
    for (i = 0; i < chiuj_label.count(); i++)
    {
        chiuj_label[i]->setText( aEk02D[iAleat2][i]);
        if (aEk02D[iAleat2][i] != "")
            chiuj_label[i]->setVisible(true);
        else
            chiuj_label[i]->setVisible(false);
    }
    this->ui->Traduko1->setText(aEk02T[iAleat2]);
    this->ui->Klarigo->setText("");
    iVortoj = 0;
    for (j = 0; j < 11; j++)
        if (aEk02D[iAleat2][j] != "")
            iVortoj++;
    for (i = 0; i < chiuj_label.count(); i++)
        chiuj_label[i]->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

    this->ui->BitBtn2->setEnabled(true);
    this->ui->BitBtn3->setEnabled(true);


}


void akuzativo::on_BitBtn2_clicked()
{
    int i;
    bool lPrava;
    lPrava = true;
    for (i = 0; i < 10; i++)
        if ( ((aFrazoElek[i] != aEk02R[iAleat2][i])) && ((aEk02R[iAleat2][i].trimmed() != "")))
            lPrava = false;
    if (lPrava)
    {
        iKorektaj++;
        this->ui->Placar1->setValue(iEk02D - iKorektaj);
        this->ui->Placar2->setValue(iKorektaj);
        Jes();

        this->ui->BitBtn3->setEnabled(false);
        this->ui->BitBtn2->setEnabled(false);

        Pauzu(1);
        aEk02A[iAleat2] = true;
    }
    else
    {
        iEraraj++;
        this->ui->Placar3->setValue(iEraraj);
        Ne();

        tekstoblinko();

    }
    this->ui->Placar4->setValue((iKorektaj * 100)/(iEraraj + iKorektaj));
    if (this->ui->Placar1->value() > 0)
        novafrazo();
    else
    {
        Mesagxo(iEraraj, iKorektaj); // prezentas gratulan mesagxon!
        on_BitBtn3_clicked();
    }
}

void akuzativo::vortoklako(int klakita)
{
    int j;
    j = klakita;
    if (aEk02R[iAleat2][j] == "1")
    {
        if (aFrazoElek[j] != "1")
        {
            chiuj_label[j]->setText( chiuj_label[j]->text() + "n" );
            chiuj_label[j]->setStyleSheet(QString::fromUtf8("color: rgb(0, 150, 0);"));
            aFrazoElek [j] = "1";
            Noteto(true);
        }
    }
    else
    {
        iEraraj++;
        this->ui->Placar3->setValue(iEraraj);
        Noteto(false);
        this->ui->Placar4->setValue((iKorektaj * 100)/(iEraraj + iKorektaj));
        chiuj_label[j]->setStyleSheet(QString::fromUtf8("color: rgb(150, 0, 0);"));
    }
    this->ui->Klarigo->setText(Klarigoj[(aEk02K[iAleat2][j]).toInt()]);

    Pauzu(1);
}

void akuzativo::tekstoblinko()
{
    this->ui->BitBtn2->setEnabled(false);
    this->ui->BitBtn3->setEnabled(false);
    QTime StartTime = QTime::currentTime();
    int iQuant = 0;
    do
    {
        QApplication::processEvents();
        if (StartTime.elapsed() >  (iQuant * Ofteco))
        {
            iQuant ++;
            for (int i = 0; i < chiuj_label.count(); i++)
            {
                if ((aFrazoElek[i] == "") &&  (aEk02R[iAleat2][i] == "1") )
                {
                    if (iQuant % 2 == 0)
                        chiuj_label[i]->setStyleSheet("color: rgb(255, 255, 255);");
                    else
                        chiuj_label[i]->setStyleSheet("color: rgb(200, 0, 0);");
                    chiuj_label[i]->repaint();
                }
            }
        }
    }
    while ( StartTime.elapsed() < (NumSec * 1000));

}

void akuzativo::on_label_164_clicked()
{
   vortoklako(0);
}

void akuzativo::on_label_165_clicked()
{
    vortoklako(1);
}

void akuzativo::on_label_166_clicked()
{
    vortoklako(2);
}

void akuzativo::on_label_167_clicked()
{
    vortoklako(3);
}

void akuzativo::on_label_168_clicked()
{
    vortoklako(4);
}

void akuzativo::on_label_169_clicked()
{
    vortoklako(5);
}

void akuzativo::on_label_170_clicked()
{
    vortoklako(6);
}

void akuzativo::on_label_171_clicked()
{
    vortoklako(7);
}

void akuzativo::on_label_172_clicked()
{
    vortoklako(8);
}

void akuzativo::on_label_173_clicked()
{
    vortoklako(9);
}

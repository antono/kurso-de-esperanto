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

#include "prononco.h"
#include "ui_prononco.h"
#include "funkcioj.h"
#include <QtGui>
#include <QtCore>


prononco::prononco(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::prononco)
{
    ui->setupUi(this);
    this->ui->PP_Prog->setVisible(false);

    Provizorujo = QDir::tempPath();
    if (Provizorujo.right(1) != "/")
        Provizorujo.append("/");

    formato.setFrequency(44100);
    formato.setChannels(1);
    formato.setSampleSize(8);
    formato.setCodec("audio/pcm");
    formato.setByteOrder( QAudioFormat::LittleEndian );
    formato.setSampleType( QAudioFormat::UnSignedInt );

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    if (!info.isFormatSupported(formato))
        formato = info.nearestFormat(formato);

    ludilo = Phonon::createPlayer(Phonon::MusicCategory,
                                  Phonon::MediaSource());

}

prononco::~prononco()
{
    delete ui;
}

void prononco::on_PP_Startu_clicked()
{

    this->ui->PP_Startu->setEnabled(false);
    this->ui->PP_Haltu->setEnabled(true);
    QString EkzercoPrononco = this->objectName().right(4);
    iEk09D = _Matriz(&aEk09D,EkzercoPrononco,"D");
    this->ui->Placar->setValue(iEk09D);
    //aEk09A.clear(iEk09D);
    aEk09A.clear();
    for (int i=0; i < iEk09D; i++)
        //aEk09A[i] = false;
        aEk09A << false;

    this->ui->PP_Haltu->setFocus();

    novafrazo();

}

void prononco::novafrazo()
{
    int i = 0;
    QString sTeksto = "";
    QString EkzercoPrononco = this->objectName().right(4);
    QString Leciono = "Lec" + EkzercoPrononco.left(2);
    if (this->ui->PP_Haltu->isEnabled())
    {
        this->ui->butonujo->setEnabled(false);
        this->ui->PP_Kiomope->setEnabled(false);
        this->ui->Tempujo->setEnabled(false);

        if (this->ui->radio1->isChecked())
            Kiome = 1;
        else
        if (this->ui->radio2->isChecked())
            Kiome = 2;
        else
        if (this->ui->radio4->isChecked())
            Kiome = 4;

        if (this->ui->Placar->value() < Kiome)
            Kiome = this->ui->Placar->value(); // Por certigi, ke en la lasta fojo ne manku vortoj

        for (i=0; i < Kiome; i++)
        {
            iAleat9 = random(iEk09D);
            while (aEk09A[iAleat9])
                iAleat9 = random(iEk09D);
            aEk09A[iAleat9] = true;
            if (aEk09D[iAleat9].toInt() > 0)
            {
                QList<QPushButton *> chiuj_butonoj =
                        this->parentWidget()->parentWidget()->parentWidget()->findChildren<QPushButton *>(Leciono + "_Button"  + aEk09D[iAleat9]);

                if (chiuj_butonoj.size() > 0)
                    aEk09T[i][0] = chiuj_butonoj.at(0)->text();
                else
                    aEk09T[i][0] = "";

                aEk09T[i][1] = "sonoj/lec" + EkzercoPrononco.left(2) + "/btn" + aEk09D[iAleat9] + mp3_finajho;
            }
            else
            {
                aEk09T[i][0] = aEk09D[iAleat9];
                sTeksto = CxSist(aEk09D[iAleat9],1);
                aEk09T[i][1] = "sonoj/lec" + EkzercoPrononco.left(2) + "/" + sTeksto + mp3_finajho;
            }
        }

        RegistrasVocxon();

        this->ui->butonujo->setEnabled(true);
        this->ui->PP_Kiomope->setEnabled(true);
        this->ui->Tempujo->setEnabled(true);

        this->ui->Placar->setValue(this->ui->Placar->value() - Kiome);
        if (this->ui->Placar->value() <= 0)
            on_PP_Haltu_clicked();
    }

}

void prononco::RegistrasVocxon()
{
    int i = 0;
    if (this->ui->PP_Haltu->isEnabled())
    {
        for (i=0; i < Kiome; i++)
        {
            if (!this->ui->PP_Haltu->isEnabled())
                break;
            this->ui->PP_Vorto->setText(aEk09T[i][0]);
            this->ui->pagharo->setCurrentIndex(1); // auskultilo

            ludilo->setCurrentSource(Loko + aEk09T[i][1]);
            ludilo->play();
            aEk09F[i] = (ludilo->totalTime()/1000) + 2;
            Pauzu( aEk09F[i]);
            this->ui->pagharo->setCurrentIndex(0); // mikrofono
            this->ui->PP_Prog->setVisible(true);
            KiomFoje = i;
            Registru(i);
            Pauzu(this->ui->spinBox->value());

            this->ui->pagharo->setCurrentIndex(2); // blanka pagho
            this->ui->PP_Prog->setVisible(false);
            this->ui->PP_Prog->setValue(0);

        }

        on_PP_Aud_re_clicked();

    }

}

void prononco::on_PP_Haltu_clicked()
{
    this->ui->PP_Kiomope->setEnabled(true);
    this->ui->pagharo->setCurrentIndex(2); // blanka pagho
    this->ui->PP_Vorto->setText(""); //
    this->ui->butonujo->setEnabled(false);
    this->ui->PP_Startu->setEnabled(true);
    this->ui->PP_Haltu->setEnabled(false);
    this->ui->Tempujo->setEnabled(true);
    this->ui->PP_Prog->setVisible(false);
    this->ui->Placar->setValue(0);
    this->ui->PP_Startu->setFocus();
}

void prononco::on_PP_Antauen_clicked()
{
    if (this->ui->Placar->value() <= 0)
        on_PP_Haltu_clicked();
    else
        novafrazo();
}

void prononco::on_PP_Mik_re_clicked()
{
    RegistrasVocxon();
}

void prononco::on_PP_Aud_re_clicked()
{
    if ( this->ui->PP_Haltu->isEnabled())
    {
        this->ui->butonujo->setEnabled(false);
        this->ui->pagharo->setCurrentIndex(1); // auskultilo
        this->ui->PP_Kiomope->setEnabled(false);
        for (int i=0; i < Kiome; i++) // ludas registritan vochon
        {
            if (!this->ui->PP_Haltu->isEnabled())
                break;
            this->ui->PP_Vorto->setText(aEk09T[i][0]);
            mp3(aEk09T[i][1]);
            Pauzu( aEk09F[i] );
            LudasRegistrita(i);
            Pauzu(this->ui->spinBox->value());
        }
        this->ui->pagharo->setCurrentIndex(2); // blanka pagho
        this->ui->butonujo->setEnabled(true);
        this->ui->PP_Kiomope->setEnabled(true);
        this->ui->PP_Vorto->setText("");
        this->ui->PP_Antauen->setFocus();
    }
}

void prononco::Registru(int KiuFojo)
{
    SonDosiero.setFileName(Provizorujo + "prononco" + QString::number(KiuFojo) + ".raw");
    SonDosiero.open( QIODevice::WriteOnly | QIODevice::Truncate);

    audio_enen = new QAudioInput( formato, this);
    connect( audio_enen, SIGNAL(notify()), SLOT(Progreso()));
    QTimer::singleShot( this->ui->spinBox->value() * 1000, this, SLOT(ChesasRegistri()));
    audio_enen->start(&SonDosiero);
}

void prononco::ChesasRegistri()
{
    audio_enen->stop();
    SonDosiero.close();
    delete audio_enen;

}

void prononco::LudasRegistrita(int KiuFojo)
{
    SonDosiero.setFileName(Provizorujo + "prononco" + QString::number(KiuFojo) + ".raw");
    SonDosiero.open( QIODevice::ReadOnly);

    audio_eksteren = new QAudioOutput(formato, this);
    connect(audio_eksteren, SIGNAL(stateChanged(QAudio::State)), SLOT(LudoFinita(QAudio::State)));
    audio_eksteren->start(&SonDosiero);

}

void prononco::LudoFinita(QAudio::State statuso)
{
    if(statuso == QAudio::IdleState)
    {
      audio_eksteren->stop();
      SonDosiero.close();
      delete audio_eksteren;
    }

}

void prononco::Progreso()
{
    int tempo = (audio_enen->processedUSecs()/ this->ui->spinBox->value()) / 10000;
    this->ui->PP_Prog->setValue( tempo );
}

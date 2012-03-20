#include "bildoludo.h"
#include "ui_bildoludo.h"
#include <QtGui>
#include <QtCore>
#include "funkcioj.h"
#include "mylabel.h"

bildoludo::bildoludo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::bildoludo)
{
    ui->setupUi(this);

    QDir dosierujo(":bildoludo");
    dosierujo.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    Dosieroj = dosierujo.entryInfoList();

    for (int i = 0; i < Dosieroj.size(); ++i)
        this->ui->BildoListo->addItem( Dosieroj.at(i).fileName());

    chiuj_bildoj = this->ui->Bildujo->findChildren<QLabel *>();
    chiuj_tekstoj = this->ui->Tekstujo->findChildren<QLabel *>();

    this->ui->Tajpujo->setEnabled(false);

}

bildoludo::~bildoludo()
{
    delete ui;
}

void bildoludo::on_BildoListo_activated(const QString &arg1)
{
    this->ui->BitBtn4->setEnabled(false);
    this->ui->BitBtn5->setEnabled(true);
    Listo.clear();
    iEk03D = Matrico(arg1);
    this->ui->Placar5->setValue(iEk03D);
    this->ui->Placar6->setValue(0);
    this->ui->Placar7->setValue(0);
    this->ui->Placar8->setValue(0);
    iKorektaj3 = 0;
    iEraraj3 = 0;
    aEk03A.resize(iEk03D);
    aPozicio.resize(iEk03D);

    for (int i = 0; i < iEk03D; i++)
        aEk03A[i] = false;

    novafrazo();
}

void bildoludo::Malaperigu()
{
    for (int i = 0; i < 5; i++)
    {
        chiuj_bildoj[i]->clear();
        chiuj_tekstoj[i]->clear();
    }
}

void bildoludo::novafrazo()
{
    int i;
    Malaperigu();
    this->ui->Tajpujo->setEnabled(false);
    this->ui->Menuo->setEnabled(false);
    this->ui->BitBtn5->setEnabled(false);

    this->ui->Musklako->clear();
    this->ui->Tajpado->clear();

    this->ui->spinBox->setFocus();

    for (i = 0; i < iEk03D; i++)
        aPozicio[i] = false;

    iAleat3 = random(iEk03D);
    while (aEk03A[iAleat3])
       iAleat3 = random(iEk03D);
    iPozicio = random(5);
    aPozicio[iAleat3] = true;
    Lotumitaj[iPozicio] = iAleat3;

    for (i = 0; i < 5; i++)
        if (i != iPozicio)
        {
           iAleat2 = random(iEk03D);
           while (aPozicio[iAleat2])
               iAleat2 = random(iEk03D);
           aPozicio[iAleat2] = true;
           Lotumitaj[i] = iAleat2;
        }


    for (i = 0; i < 5; i++)
    {
          if (this->ui->BitBtn4->isEnabled())
                  return;
          QPixmap Bildo(Dosieroj.at(Lotumitaj[i]).filePath());  // + Dosieroj.at(Lotumitaj[i]).fileName());
          chiuj_bildoj[i]->setPixmap(Bildo);
          if (this->ui->Elementoj->isChecked())
              chiuj_tekstoj[i]->clear();
          else
              chiuj_tekstoj[i]->setText(Listo[Lotumitaj[i]]);

          if (!this->ui->nur_teksto->isChecked())
          {
              mp3("sonoj/bildoludo/" + this->ui->BildoListo->currentText() + "/" + Listo[Lotumitaj[i]] + mp3_finajho);
              // LUDAS MP3
          }

          Pauzu(this->ui->spinBox->value());
    }

    JamKlakis = false;
    demandas();

}

int bildoludo::Matrico(const QString ek)
{
    QString sTeksto;
    QDir dosierujo(":bildoludo/" + ek);
    dosierujo.setFilter(QDir::Files);

    QStringList filtroj;
    filtroj << "*.png";

    dosierujo.setNameFilters(filtroj);

    Dosieroj = dosierujo.entryInfoList();
    QString DosierNomo;
    for (int i = 0; i < Dosieroj.size(); ++i)
    {
        QFileInfo fileInfo = Dosieroj.at(i);
        DosierNomo = fileInfo.fileName();
        sTeksto = DosierNomo.replace(".png", "");
        Listo << CxSist(sTeksto, 3);

    }
    return Listo.size();
}


void bildoludo::on_BitBtn5_clicked()
{
    this->ui->BitBtn4->setEnabled(true);
    this->ui->BitBtn5->setEnabled(false);
    Malaperigu();
    this->ui->Musklako->clear();
    this->ui->Tajpujo->setEnabled(false);
    this->ui->Menuo->setEnabled(true);
    this->ui->BildoListo->setFocus();
}

void bildoludo::demandas()
{
    int i;

    if (this->ui->stilo_klavaro->isChecked())
    {
        Malaperigu();
        QPixmap Bildo(Dosieroj.at(iAleat3).filePath());
        this->ui->Image3->setPixmap(Bildo);
        this->ui->Tajpado->clear();
        this->ui->Tajpujo->setEnabled(true);
        this->ui->Tajpado->setFocus();
    }
    else
    {

        for (i = 0; i < 5; i++)
            Lotumitaj3[i] = -1;

        for (i = 0; i < 5; i++)
        {
            iAleat2 = random(5);
            while ((Lotumitaj3[iAleat2] >= 0) || (Lotumitaj3[iAleat2] == iAleat3))
                iAleat2 = random(5);
            Lotumitaj2[i] = Lotumitaj[iAleat2];
            Lotumitaj3[iAleat2] = 0;
            QPixmap Bildo(Dosieroj.at(Lotumitaj2[i]).filePath());
            chiuj_bildoj[i]->setPixmap(Bildo);

            chiuj_tekstoj[i]->clear();

            if (Lotumitaj2[i] == iAleat3)
                iPozicio = i;
        }

        this->ui->Musklako->setText(Listo[iAleat3]);


        if (!this->ui->nur_teksto->isChecked())
        {
            mp3("sonoj/bildoludo/" + this->ui->BildoListo->currentText() + "/" + Listo[iAleat3] + mp3_finajho);
            // LUDAS MP3
        }
    }

    this->ui->Menuo->setEnabled(true);
    this->ui->BitBtn5->setEnabled(true);

}

void bildoludo::bildoklako(int klakita)
{
    if ((this->ui->stilo_klavaro->isChecked()) || (JamKlakis))
        return;
    JamKlakis = true;

    if (klakita == iPozicio)
    {
        iKorektaj3++;
        this->ui->Placar5->setValue(iEk03D - iKorektaj3);
        this->ui->Placar6->setValue(iKorektaj3);
        Jes();
        Pauzu(2);
        aEk03A[iAleat3] = true;
    }
    else
    {
        iEraraj3++;
        this->ui->Placar7->setValue(iEraraj3);
        Ne();
        bildoblinko(iPozicio);

    }
    this->ui->Placar8->setValue((iKorektaj3 * 100)/ (iEraraj3 + iKorektaj3));
    if (this->ui->Placar5->value() > 0)
        novafrazo();
    else
    {
        Mesagxo(iEraraj3, iKorektaj3); //{ prezentas gratulon mesagxon! }
        this->ui->Musklako->clear();
        Malaperigu();
        this->ui->BildoListo->setFocus();
        this->ui->BitBtn4->setEnabled(true);
        this->ui->BitBtn5->setEnabled(false);
    }
    JamKlakis = false;

}

void bildoludo::bildoblinko(int korekta)
{
    QTime StartTime = QTime::currentTime();
    int iQuant = 0;
    QString olda = chiuj_bildoj[korekta]->styleSheet();
    do
    {
        QApplication::processEvents();
        if (StartTime.elapsed() >  (iQuant * Ofteco))
        {
            iQuant ++;
            if (iQuant % 2 == 0)
                chiuj_bildoj[korekta]->setStyleSheet("background-color: rgb(255, 255, 255);");
            else
                chiuj_bildoj[korekta]->setStyleSheet("background-color: rgb(200, 0, 0);");
            chiuj_bildoj[korekta]->repaint();
        }
    }
    while ( StartTime.elapsed() < (NumSec * 1000));

    chiuj_bildoj[korekta]->setStyleSheet(olda);

}


void bildoludo::on_Butono_clicked()
{
    bool lPrava;
    QString sTeksto = purigas(this->ui->Tajpado->text(), true );
    if (sTeksto == "")
        return;

    lPrava = (sTeksto == Listo[iAleat3]);
    if (lPrava)
    {
        iKorektaj3++;
        this->ui->Placar5->setValue(iEk03D - iKorektaj3);
        this->ui->Placar6->setValue(iKorektaj3);
        Jes();
        Pauzu(1);
        aEk03A[iAleat3] = true;
    }
    else
    {
        iEraraj3++;
        this->ui->Placar7->setValue(iEraraj3);
        Ne();
        tekstoblinko();
    }

    this->ui->Placar8->setValue((iKorektaj3 * 100)/(iEraraj3+iKorektaj3));
    if (this->ui->Placar5->value() > 0)
        novafrazo();
    else
    {
        Mesagxo(iEraraj3, iKorektaj3); // { prezentas gratulon mesagxon! }
        this->ui->Tajpujo->setEnabled(false);
        this->ui->Image3->clear();
        this->ui->BildoListo->setFocus();
        this->ui->BitBtn4->setEnabled(true);
        this->ui->BitBtn5->setEnabled(false);
    }
}

void bildoludo::tekstoblinko()
{
    this->ui->Label3->setText(Listo[iAleat3]);
    QTime StartTime = QTime::currentTime();
    int iQuant = 0;
    QString olda = this->ui->Label3->styleSheet();
    do
    {
        QApplication::processEvents();
        if (StartTime.elapsed() >  (iQuant * Ofteco))
        {
            iQuant ++;
            if (iQuant % 2 == 0)
                this->ui->Label3->setStyleSheet("color: rgb(255, 255, 255);");
            else
                this->ui->Label3->setStyleSheet("color: rgb(200, 0, 0);");
            this->ui->Label3->repaint();
        }
    }
    while ( StartTime.elapsed() < (NumSec * 1000));

    this->ui->Label3->setStyleSheet(olda);
    this->ui->Label3->clear();
}

void bildoludo::on_Image1_clicked()
{
    if (this->ui->stilo_muso->isChecked())
        bildoklako(0);
}

void bildoludo::on_Image2_clicked()
{
    if (this->ui->stilo_muso->isChecked())
        bildoklako(1);
}

void bildoludo::on_Image3_clicked()
{
    if (this->ui->stilo_muso->isChecked())
        bildoklako(2);
}

void bildoludo::on_Image4_clicked()
{
    if (this->ui->stilo_muso->isChecked())
        bildoklako(3);
}

void bildoludo::on_Image5_clicked()
{
    if (this->ui->stilo_muso->isChecked())
        bildoklako(4);
}

void bildoludo::on_Tajpado_returnPressed()
{
    on_Butono_clicked();
}

void bildoludo::on_stilo_muso_clicked()
{
    //this->ui->Tajpujo->setEnabled(false);
}

void bildoludo::on_BitBtn4_clicked()
{
    on_BildoListo_activated(this->ui->BildoListo->currentText());
}

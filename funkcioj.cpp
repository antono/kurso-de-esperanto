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

#include <cstdlib>
#include <ctime>
#include "sleeper.h"
#include <QtGui>
#include <QtCore>
#include <funkcioj.h>
#include "kurso.h"
#include <neklakebla.h>
#include <klakbutono.h>
#include <label_sago_reversa.h>
#include <label_sago.h>
#include <label_klakebla.h>


// eksteraj variabloj, uzotaj dum la tuta programo

int NumSec = 3;
int Ofteco = 400;
QSettings Konfiguro;
QSettings Tradukado;
QString sLingvo, sTiparo, sTiparoEo, sTradukoDosiero, sKorNomo, sKorAdreso, EkzercoAkuzativoTrad;
int iSistemo = 0, LastaLeciono = 1, LastaPagxo = 1, iLastaFojo = 0, iLiterGrando, iLiterGrandoEo, iFenestraStilo;
bool lKorektanto, lCxapeligo, Tradukilo, NeEkzistasTraduko, lSxaltilo, lNoteto;
QString sTradukinto;
QString Loko;
QString Direkto;


// eksteraj variabloj, uzotaj por komunikighi kun la uzulo
QString smRekomencu,
        smGratulon,
        smDenove,
        smModifis,
        smTondujo,
        smDevasHaviKor,
        smDevasSavi,
        smKoverto,
        smDisketo,
        smPordo,
        smLigilo,
        Antauen,
        Nuligi,
        smNeSono;

int  _Matriz(QStringList * Mat, QString ek, QString tipo)
{
    int i = 0;
    QStringList Listo;
    Mat->clear();
    if (tipo == "T")
    {
        QSettings Tradukado(Loko + "tradukoj/" + sTradukoDosiero, QSettings::IniFormat);
        Tradukado.setIniCodec("UTF-8");
        Tradukado.beginGroup("Ekzerco-" + ek);
        Listo = Tradukado.allKeys();
        for (i = 0; ( i < Listo.count()); i++)
            Mat->append( Tradukado.value(QString::number(i), "Ne tradukita").toString() );
    }
    else
    {
        QSettings Ekzerco(":ekzercoj/ekz" + ek.left(2) + ".dat", QSettings::IniFormat);
        Ekzerco.setIniCodec("UTF-8");
        Ekzerco.beginGroup(ek+tipo);
        Listo = Ekzerco.allKeys();
        for (i = 0; ( i < Listo.count()); i++)
            Mat->append( Ekzerco.value(QString::number(i)).toString() );
    }
    return Listo.count();
}

int  _Matriz2(QList<QStringList> * Mat, QString ek, QString tipo, int minimuma)
{
    int  i = 0, j = 0, k = 0, m = 0;
    QString sTemp, sTemp2 = "";
    QStringList Listo;

    QSettings F(":ekzercoj/ekz" + ek.left(2) + ".dat", QSettings::IniFormat);
    F.setIniCodec("UTF-8");
    F.beginGroup(ek + tipo);
    Listo = F.allKeys();
    //Mat->resize(Listo.size());
    //for (i=0; i < minimuma; i++)
    //    Malplena << "";
    Mat->clear();
    for (i = 0; ( i < Listo.count()); i++)
    {
        sTemp = F.value(QString::number(i), "").toString();
        sTemp2 = "";
        k = 0;
        QStringList Malplena;
        //Mat->append(Malplena);
        for (j=0; j < sTemp.size(); j++)
            if (sTemp.mid(j,1) != "~")
                sTemp2 += sTemp.mid(j,1);
            else
            {
                //Mat->at(i).append( sTemp2 );
                Malplena << sTemp2;
                k++;
                sTemp2 = "";
            }
        //Mat->at(i).append(sTemp2);
        Malplena << sTemp2;
        for (m = Malplena.size(); m < minimuma; m++)
            //Mat->at(i).append("");
            Malplena << "";
        Mat->append(Malplena);
    }
    return Listo.count();
}

int random(int limo)
{
    float randoma = static_cast<float>(qrand());
    float unua = static_cast<float>( limo * randoma );
    float dua = RAND_MAX + 1.0;
    int rezulto = static_cast<int>( unua / dua);
    return rezulto;
    //return int((limo * qrand()) / (RAND_MAX + 1.0));

}

QString CxSist(QString frazo, int iSistemo)
{
    QString malnova, nova;
    QString chapeloj[12] = {
        QString::fromUtf8("ĉ"),
        QString::fromUtf8("ĝ"),
        QString::fromUtf8("ĥ"),
        QString::fromUtf8("ĵ"),
        QString::fromUtf8("ŝ"),
        QString::fromUtf8("ŭ"),
        QString::fromUtf8("Ĉ"),
        QString::fromUtf8("Ĝ"),
        QString::fromUtf8("Ĥ"),
        QString::fromUtf8("Ĵ"),
        QString::fromUtf8("Ŝ"),
        QString::fromUtf8("Ŭ") };
    QString surogato[2][12] = {
                               {"cx", "gx", "hx", "jx", "sx", "ux",
                                "Cx", "Gx", "Hx", "Jx", "Sx", "Ux"},
                               {"ch", "gh", "hh", "jh", "sh", "u",
                                "Ch", "Gh", "Hh", "Jh", "Sh", "U"}};
    if (iSistemo == 0)
        return frazo;
    else {
        QString provizora = frazo;
        if (iSistemo == 3)
        {
            for (int i=0; i < 12; i++)
            {
                nova = chapeloj[i];
                malnova =  surogato[0][i];
                provizora.replace(malnova, nova);
            }

        }

        else
        {
            for (int i=0; i < 12; i++)
            {
                malnova = chapeloj[i];
                nova =  surogato[iSistemo-1][i];
                provizora.replace(malnova, nova);
            }
        }
        return provizora;
    }
}

void Pauzu(int sekundoj)
{
    QTime StartTime = QTime::currentTime();
    do
    {
        QApplication::processEvents();
    }
    while ( StartTime.elapsed() < (sekundoj * 1000));

}


QString purigas(QString teksto, bool minuskle)
{
    int i;
    while ((i = teksto.count("  ")) > 0)
        teksto.replace("  ", " ");
    teksto = teksto.trimmed();
    teksto.remove(".");
    teksto.remove(",");
    if (minuskle)
        teksto = teksto.toLower();
    return teksto;
}

void Ne()
{
    if (lNoteto)
    {
        mp3("sonoj/noteto_ne" + mp3_finajho);
        Pauzu(2);
    }

    if (lSxaltilo)
    {
        int iAleat = 0;

        QDir sonoj(Loko + "sonoj/");
        QStringList filtriloj;
        filtriloj << "ne?" + mp3_finajho;
        sonoj.setNameFilters(filtriloj);
        int kvanto = sonoj.count();
        iAleat = random(kvanto);
        QString dosiernomo = "sonoj/" + sonoj.entryList().at(iAleat);

        mp3(dosiernomo);
    }
}

void Jes()
{
    if (lNoteto)
    {
        mp3("sonoj/noteto_jes" + mp3_finajho);
        Pauzu(2);
    }

    if (lSxaltilo)
    {
        int iAleat;
        QString sMp3dos;
        iAleat = random(6);
        while (iAleat == iLastaFojo)
            iAleat = random(6);
        switch (iAleat) {
        case 0: sMp3dos = "jes"; break;
        case 1: sMp3dos = "trebone"; break;
        case 2: sMp3dos = "bonege"; break;
        case 3: sMp3dos = "prave"; break;
        case 4: sMp3dos = "trafe"; break;
        case 5: sMp3dos = "korekte"; break;
        default: sMp3dos = "jes";
        }
        iLastaFojo = iAleat;
        QDir sonoj(Loko + "sonoj/");
        QStringList filtriloj;
        filtriloj << sMp3dos + "?" + mp3_finajho;
        sonoj.setNameFilters(filtriloj);
        int kvanto = sonoj.count();
        iAleat = random(kvanto);
        QString dosiernomo = "sonoj/" + sonoj.entryList().at(iAleat);

        mp3(dosiernomo);
    }
}

void Noteto(bool prava)
{
    if (lNoteto)
    {
        if (prava)
            mp3("sonoj/noteto_jes" + mp3_finajho);
        else
            mp3("sonoj/noteto_ne" + mp3_finajho);
    }
}

void Mesagxo(int iEraraj, int iKorektaj)
{
    QMessageBox msgBox(QApplication::activeWindow());

    if (((iKorektaj * 100) / (iEraraj + iKorektaj)) >= 70 )
    {
        if (lSxaltilo)
        {
            int iAleat = random(8), i=0;
            QString dosiernomo;
            iAleat = random(8);
            dosiernomo = "sonoj/gratulo" + QString::number(iAleat+1) + mp3_finajho;
            QFile dosiero(dosiernomo);
            while ( ! dosiero.exists() && i < 8)
            {
                iAleat = random(8);
                dosiernomo = "sonoj/gratulo" + QString::number(iAleat+1) + mp3_finajho;
                QFile dosiero(dosiernomo);
                i++;
            }

            mp3(dosiernomo);

        }
        else if (lNoteto)
            mp3("sonoj/noteto_jes" + mp3_finajho);

        msgBox.setText(smGratulon);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }

    else
    {
        if (lSxaltilo)
        {
            int iAleat = random(8), i=0;
            QString dosiernomo;
            iAleat = random(8);
            dosiernomo = "sonoj/nebona" + QString::number(iAleat+1) + mp3_finajho;
            QFile dosiero(dosiernomo);
            while ( ! dosiero.exists() && i < 8)
            {
                iAleat = random(8);
                dosiernomo = "sonoj/nebona" + QString::number(iAleat+1) + mp3_finajho;
                QFile dosiero(dosiernomo);
                i++;
            }

            mp3(dosiernomo);

        }
        else if (lNoteto)
            mp3("sonoj/noteto_ne" + mp3_finajho);

        msgBox.setText(smDenove);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void Sinkronigu()
{
    /*
      Se necese, ni entajpu chi tie la kodon por sinkronigi la sonon de mp3-dosieroj.
    */
}


void Trad(QWidget * Pagxaro, QString Patro)
{
    QSettings Tradukado(Loko + "tradukoj/" + sTradukoDosiero, QSettings::IniFormat);
    Tradukado.setIniCodec("UTF-8");
    // QString Direkto = Tradukado.value("Traduko/Direkto", "LTR").toString();
    QList<QLabel *> chiuj_label =  Pagxaro->findChildren<QLabel *>();
    QList<neklakebla *> chiuj_neklakebla =  Pagxaro->findChildren<neklakebla *>();
    QList<klakbutono *> chiuj_klak =  Pagxaro->findChildren<klakbutono *>();
    QString Tradukota;
    int j;

    // Shanghas la ikonon de la sago kaj reversa sago, lau la lingvo-direkto
    QList<label_sago_reversa *> chiuj_sagoj_reversaj = Pagxaro->findChildren<label_sago_reversa *>();
    QList<label_sago *> chiuj_sagoj = Pagxaro->findChildren<label_sago *>();
    QPixmap Bildo1, Bildo2;
    QString RTL_Marko, LTR_Marko;
    LTR_Marko = QString::fromUtf8("\u200E");
    RTL_Marko = QString::fromUtf8("\u200F");

    if (Direkto == "LTR")
    {
         Bildo1 = QPixmap(":ikonoj/sago_revena.png");
         Bildo2 = QPixmap(":ikonoj/sago_antauen.png");
    }
    else
    {
         Bildo1 = QPixmap(":ikonoj/sago_revena_RTL.png");
         Bildo2 = QPixmap(":ikonoj/sago_antauen_RTL.png");
    }

    for (j = 0; j < chiuj_sagoj_reversaj.count(); j++)
    {
        chiuj_sagoj_reversaj[j]->setPixmap(Bildo1);
        chiuj_sagoj_reversaj[j]->setStyleSheet( Direkto == "LTR" ?  "margin-left: 15px;" : "margin-right: 15px;");
    }

    for (j = 0; j < chiuj_sagoj.count(); j++)
        chiuj_sagoj[j]->setPixmap(Bildo2);

    // Aldonas LTR-markon  al la komenco/fino de ĉiu butona frazo en Eo, por ke Qt korekte montru la interpunkcion, kiam la tradukita lingvo estas RTL.
    for (j = 0; j < chiuj_neklakebla.count(); j++)
        chiuj_neklakebla[j]->setText( LTR_Marko + chiuj_neklakebla[j]->text() + LTR_Marko );

    for (j = 0; j < chiuj_klak.count(); j++)
        chiuj_klak[j]->setText(chiuj_klak[j]->text() + LTR_Marko);
    //

    for (int i = 0; i < chiuj_label.count(); i++)
    {
        if ( chiuj_label[i]->objectName().left(5) == Patro )
        {
            Tradukota = (qobject_cast<label_klakebla *>(chiuj_label[i]) ) ?   chiuj_label[i]->objectName().mid(12) : chiuj_label[i]->objectName().mid(6);
            chiuj_label[i]->setText(  Tradukado.value(Patro + "/" + Tradukota, "Ne Tradukita").toString() );
        }
        else
        {

            QString objekto_nomo = (qobject_cast<label_klakebla *>(chiuj_label[i]) ) ?  chiuj_label[i]->objectName().mid(12) : chiuj_label[i]->objectName();
            if ( objekto_nomo == "Ekz_Plen2" )
            {
                Tradukota = ( chiuj_label[i]->parentWidget()->objectName().mid(5,1) != "B") ?  "TFrame41.Label84" : "Frame42.Label84";
                chiuj_label[i]->setText( Tradukado.value(Patro + "/" + Tradukota, "Ne Tradukita").toString());
            }
            else
            {
                Tradukota = "";
                if ( objekto_nomo == "Ekz_Akuz1" )
                    Tradukota = "TFrame5.Label6";
                if ( objekto_nomo == "Ekz_Akuz2" )
                    Tradukota = "TFrame5.Label1";

                if ( objekto_nomo == "Ekz_Pron1" )
                    Tradukota = "TFrame2.PP_Label1";
                if ( objekto_nomo == "Ekz_Pron2" )
                    Tradukota = "TFrame2.PP_Label41";

                if ( objekto_nomo == "Ekz_Audk1" )
                    Tradukota = "TFrame3.Label59";
                if ( objekto_nomo == "Ekz_Audk2" )
                    Tradukota = "TFrame3.Label68";

                if ( objekto_nomo == "Ekz_Vort1" )
                    Tradukota = "TFrame4.Label83";
                if ( objekto_nomo == "Ekz_Vort2" )
                    Tradukota = "TFrame1.Label7";

                if ( objekto_nomo == "Ekz_Plen1" )
                    Tradukota = "TFrame4.Label83";


                if (Tradukota != "")
                    chiuj_label[i]->setText( Tradukado.value("Gheneralaj/" + Tradukota, "Ne Tradukita").toString());
                else
                {
                    QVariant tipo =  chiuj_label[i]->property("tipo");
                    if ( tipo.isValid() && tipo == "esperanta")
                    {
                        if (Direkto == "RTL")
                        {
                            chiuj_label[i]->setText( chiuj_label[i]->text() + LTR_Marko);
                            chiuj_label[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                        }
                        else
                            chiuj_label[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                    }
                    if (chiuj_label[i]->objectName().left(8) == "ripetata")
                    {
                        if (Direkto == "LTR")
                        {
                            chiuj_label.at(i)->setText(QString::fromUtf8("   \u201D   \u201D   \u201D"));
                        }
                        else
                            chiuj_label.at(i)->setText( "===" + RTL_Marko );
                    }
                }

            }
        }
    }


}


void  Adiau()
{
    if (lSxaltilo)
    {
        int iAleat;

        QString sMp3dos;
        iAleat = random(4);
        switch (iAleat)
        {
        case 0: sMp3dos = "ghis"; break;
        case 1: sMp3dos = "revido"; break;
        case 2: sMp3dos = "baldau"; break;
        case 3: sMp3dos = "adiau"; break;
        default: sMp3dos = "revido"; break;
        }
        QDir sonoj(Loko + "sonoj/");
        QStringList filtriloj;
        filtriloj << sMp3dos + "?" + mp3_finajho;
        sonoj.setNameFilters(filtriloj);
        int kvanto = sonoj.count();
        iAleat = random(kvanto);
        QString dosiernomo = "sonoj/" + sonoj.entryList().at(iAleat);

        mp3(dosiernomo);
    }
}

void SxargxasEk(QTabWidget * Pagxaro, bool Savas)
{
    int i,j;
    QString teksto;
    QString Patro = Pagxaro->objectName();

    //QList<QWidget *> chiuj_tab = Pagxaro->findChildren<QWidget *>();
    QList<QWidget *> chiuj_tab;
    for (i=0; i < Pagxaro->count(); i++)
         chiuj_tab << Pagxaro->widget(i);

    QSettings Konfiguro(QSettings::IniFormat, QSettings::UserScope,
                        "Esperanto", "Kurso4");

    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup(Patro);

    for (j=0; j < chiuj_tab.count(); j++)
    {
        if (chiuj_tab.at(j)->objectName().left(6) == "Sendas")
        {
            QList<QLineEdit *> chiuj_edit = chiuj_tab.at(j)->findChildren<QLineEdit *>();
            QList<QPlainTextEdit *> chiuj_memo = chiuj_tab.at(j)->findChildren<QPlainTextEdit *>();
            for (i=0; i < chiuj_edit.count(); i++)
            {
                if (Savas)
                {
                    teksto = chiuj_edit[i]->text();
                    Konfiguro.setValue(chiuj_edit[i]->objectName(), teksto);
                }
                else
                {
                    teksto = (Konfiguro.value(chiuj_edit[i]->objectName(), "")).toString();
                    chiuj_edit[i]->insert(teksto);
                }
            }

            for (i=0; i < chiuj_memo.count(); i++)
            {
                if (Savas)
                {
                    teksto = chiuj_memo[i]->toPlainText();
                    Konfiguro.setValue(chiuj_memo[i]->objectName(), teksto);
                }
                else
                {
                    teksto = (Konfiguro.value(chiuj_memo[i]->objectName(), "")).toString();
                    chiuj_memo[i]->insertPlainText(teksto);
                }
            }
        }
    }
    Konfiguro.endGroup();
}

void SavasEk(QTabWidget * Pagxaro)
{
    int i,j;
    QString teksto;
    QString Patro = Pagxaro->objectName();

    QList<QWidget *> chiuj_tab = Pagxaro->findChildren<QWidget *>();
    QSettings Konfiguro(QSettings::IniFormat, QSettings::UserScope,
                        "Esperanto", "Kurso4");

    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup(Patro);

    for (j=0; j < chiuj_tab.count(); j++)
    {
        if (chiuj_tab.at(j)->objectName().left(6) == "Sendas")
        {
            QList<QLineEdit *> chiuj_edit = chiuj_tab.at(j)->findChildren<QLineEdit *>();
            QList<QPlainTextEdit *> chiuj_memo = chiuj_tab.at(j)->findChildren<QPlainTextEdit *>();
            for (i=0; i < chiuj_edit.count(); i++)
            {
                teksto = chiuj_edit[i]->text();
                Konfiguro.setValue(chiuj_edit[i]->objectName(), teksto);
            }

            for (i=0; i < chiuj_memo.count(); i++)
            {
                teksto = chiuj_memo[i]->toPlainText();
                Konfiguro.setValue(chiuj_memo[i]->objectName(), teksto);
            }
        }
    }
    Konfiguro.endGroup();
    Konfiguro.sync();
}

void Sendas(QWidget * Pagxo, int PagxoNumero)
{
    QString Sendota = "";
    int i;
    QString NomoPatro = Pagxo->parent()->parent()->objectName().mid(3,2);
    QString Leciono = "Leciono " + NomoPatro;
    QList<QLabel *> chiuj_label;

    if ( NomoPatro != "13")
    {
        chiuj_label = Pagxo->findChildren<QLabel *>();
        Sendota.append(Leciono + QString::fromUtf8(" - Paĝo "));
        Sendota.append( QString::number(PagxoNumero) +  "\n\n" );
    }
    else
    {
        QTabWidget * ekzamen_pagho = qobject_cast<QTabWidget*>(Pagxo->parent()->parent());
        for ( i = 0; i < 5; i++ )
            chiuj_label = chiuj_label + ekzamen_pagho->widget(i)->findChildren<QLabel *>();
    }
    QString TextoEdit, TextoLabel;
    QLineEdit * amiketo;
    QPlainTextEdit * amiketo2;
    for ( i = 0; i < chiuj_label.count(); i++)
    {
        if (chiuj_label[i]->buddy() > 0)
        {
            TextoLabel = chiuj_label[i]->text().trimmed();
            amiketo = qobject_cast<QLineEdit*>(chiuj_label[i]->buddy());
            if (amiketo > 0)
                TextoEdit = amiketo->text();
            else
            {
                amiketo2 = qobject_cast<QPlainTextEdit*>(chiuj_label[i]->buddy());
                if (amiketo2 > 0)
                    TextoEdit = "\n\n" + amiketo2->toPlainText();
                else
                {
                    TextoEdit = "";
                    TextoLabel = "";
                }
            }

            if (TextoLabel != "")
                Sendota.append(TextoLabel + "\n");
            if (TextoEdit != "")
                Sendota.append(TextoEdit + "\n\n");
        }
        else
            Sendota.append(chiuj_label[i]->text() + "\n\n");
    }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(CxSist(Sendota, iSistemo) );
    QMessageBox msgBox(QApplication::activeWindow());
    msgBox.setText(smTondujo);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void Sendas_Printilo(QTabWidget * Pagxaro, QString Patro, QProgressBar * prog_printilo)
{
    QPrinter printer(QPrinter::HighResolution);
    if (Patro == "Leciono 13")
        Patro = "Fina Ekzameno";
    printer.setDocName(Patro);

    QPrintDialog *dialog = new QPrintDialog(&printer, Pagxaro);

    if (dialog->exec() != QDialog::Accepted)
        return;

    QPainter painter;
    painter.begin(&printer);
    int margheno = 70;

    double xscale = printer.pageRect().width()/double(Pagxaro->currentWidget()->width() + margheno * 2);
    double yscale = (printer.pageRect().height() / 2) / double(Pagxaro->currentWidget()->height() + margheno * 2);
    int Alteco = Pagxaro->currentWidget()->height() ;
    double scale = qMin(xscale, yscale);

    painter.scale(scale, scale);

    QFont font = QApplication::font();
    painter.translate(margheno, margheno);
    font.setPixelSize(20);
    painter.setFont( font );
    painter.drawText(0, 0, "Kurso de Esperanto  -  " + Patro + "   (kurso.com.br)" );

    prog_printilo->setVisible(true);
    prog_printilo->setMaximum(Pagxaro->count()+1);
    prog_printilo->reset();

    int olda_indekso = Pagxaro->currentIndex();

    bool NovaPagho = false;

    for (int i = 0; i < (Pagxaro->count()); i++)
    {
        Pagxaro->setCurrentIndex(i);
        QApplication::processEvents();
        if (Pagxaro->currentWidget()->objectName().left(7) != "Ekzerco")
        {
            Pagxaro->currentWidget()->render(&painter, Pagxaro->currentWidget()->pos(),
                                             Pagxaro->currentWidget()->rect(),
                                             QWidget::RenderFlags(QWidget::DrawChildren));
            if (!NovaPagho)
            {
                NovaPagho = true;
                painter.translate(0, Alteco + margheno);
            }
            else
                if (i < Pagxaro->count()-1){
                    printer.newPage();
                    painter.translate(0, (margheno + Alteco) * -1);
                    NovaPagho = false;
                }
        }
        prog_printilo->setValue(i+1);
    }

    Pagxaro->setCurrentIndex(olda_indekso);
    prog_printilo->reset();
    prog_printilo->setVisible(false);
    painter.end();

}

void mp3(QString Dosiero)
{
    static kurso * chefa_fenestro = (kurso *)QApplication::activeWindow();

    if (chefa_fenestro != 0)
    {
        chefa_fenestro->ludilo->setCurrentSource(Loko + Dosiero.toLower());
        chefa_fenestro->ludilo->play();
    }

}

void tekstoblinko(QWidget * korekta)
{
    // Montras la korektan
    int iQuant = 0;
    QString olda = korekta->styleSheet();
    QString Rugha, Blanka;
    QRadioButton * testo;
    testo = qobject_cast<QRadioButton *>(korekta);
    if (testo > 0)
    {
        Blanka = "background: lightBlue;";
        Rugha = "background: white;";
    }
    else
    {
        Rugha = "color: red; font-size: " + QString::number(korekta->font().pixelSize()) + "px; font-family: " + korekta->font().family();
        Blanka = "color: white; font-size: " + QString::number(korekta->font().pixelSize()) + "px; font-family: " + korekta->font().family();
    }
    QTime StartTime = QTime::currentTime();
    do
    {
        QApplication::processEvents();
        if (StartTime.elapsed() >  (iQuant * Ofteco))
        {
            iQuant ++;
            if (iQuant % 2 == 0)
                korekta->setStyleSheet(Blanka);
            else
                korekta->setStyleSheet(Rugha);
            korekta->update();
        }
    }
    while ( StartTime.elapsed() < (NumSec * 1000));

    korekta->setStyleSheet(olda);
}

void randomize()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

QString helpdosiero(QString tipo)
{
    QFile dosiero("");
    QString dosiernomo = sTradukoDosiero;
    if (tipo == "kio")
    {
        dosiernomo = Loko + "tradukoj/kio/kio_" + dosiernomo.replace(".trd", ".html");
        dosiero.setFileName(dosiernomo);
        if (dosiero.exists())
            return("file:///" + dosiernomo);
        else
            return("file:///" + Loko + "tradukoj/kio/kio_angla.html" );
    }
    else
    {
        dosiernomo = Loko + "tradukoj/kiel/kiel_" + dosiernomo.replace(".trd", ".html");
        dosiero.setFileName(dosiernomo);
        if (dosiero.exists())
            return("file:///" + dosiernomo);
        else
            return("file:///" + Loko + "tradukoj/kiel/kiel_angla.html" );

    }
}

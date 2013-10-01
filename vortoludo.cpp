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

#include "vortoludo.h"
#include "ui_vortoludo.h"
#include "funkcioj.h"
#include <QtGui>
#include <QtCore>

vortoludo::vortoludo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::vortoludo)
{
    ui->setupUi(this);
    this->ui->Grupo->setVisible(false);
}

vortoludo::~vortoludo()
{
    delete ui;
}

void vortoludo::on_BitBtn18_clicked()
{
    /*
    if (Direkto == "RTL")
        ui->Vorto->setStyleSheet("qproperty-alignment: AlignRight;");
    else
        ui->Vorto->setStyleSheet("qproperty-alignment: AlignLeft;");
    */

    chiuj_radioj = this->ui->Grupo->findChildren<QRadioButton *>();
    QString EkzercoVortoLudo = this->objectName().right(4);
    Leciono = this->objectName().left(6);
    iAktualaPagho = ((QTabWidget*)this->parentWidget()->parentWidget()->parentWidget())->currentIndex();
    iEk03D = _Matriz(&aEk03D,EkzercoVortoLudo,"D");
    _Matriz(&aEk03R,EkzercoVortoLudo,"R");
    this->ui->BitBtn18->setEnabled(false);
    this->ui->BitBtn20->setEnabled(true);
    // this->ui->printilo_ps->setEnabled(false);
    //aEk03A.clear(iEk03D);
    //aPozicio.clear(iEk03D);
    aEk03A.clear();
    aPozicio.clear();
    for (int i = 0; i < iEk03D; i++)
    {
        //aEk03A[i] = false;
        aEk03A << false;
        aPozicio << false;
    }
    this->ui->Placar1->setValue(iEk03D);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj3 = 0;
    iEraraj3 = 0;
    this->ui->Grupo->setVisible(true);
    JamKlakis = false;
    novafrazo();
    this->ui->Grupo->setFocus();
}

void vortoludo::on_BitBtn20_clicked()
{
    this->ui->BitBtn18->setEnabled(true);
    this->ui->BitBtn20->setEnabled(false);
    this->ui->Grupo->setVisible(false);
    // this->ui->printilo_ps->setEnabled(true);
    this->ui->BitBtn18->setFocus();
}

void vortoludo::grupoclick(int klakita)
{
    if (JamKlakis)
        return;
    ui->Grupo->setEnabled(false);
    JamKlakis = true;

    if (klakita == iPozicio)
    {
        Jes();
        iKorektaj3++;
        this->ui->Placar2->setValue(iKorektaj3);
        this->ui->Placar1->setValue(iEk03D - iKorektaj3);
        aEk03A[iAleat3] = true;
        Pauzu(2);
    }
    else
    {
        Ne();
        iEraraj3++;
        this->ui->Placar3->setValue(iEraraj3);
        this->ui->Grupo->setEnabled(false);

        tekstoblinko(chiuj_radioj[iPozicio]);

        this->ui->Grupo->setEnabled(true);

    }
    this->ui->Placar4->setValue((iKorektaj3 * 100)/ (iEraraj3 + iKorektaj3));
    if (iKorektaj3 < iEk03D)
    {
        novafrazo();
        if (iAktualaPagho == ((QTabWidget*)this->parentWidget()->parentWidget()->parentWidget())->currentIndex() )
            this->ui->Grupo->setFocus();
    }
    else
    {
        Mesagxo(iEraraj3, iKorektaj3);
        on_BitBtn20_clicked();
    }
    chiuj_radioj[klakita]->setAutoExclusive(false);
    chiuj_radioj[klakita]->setChecked(false);
    chiuj_radioj[klakita]->setAutoExclusive(true);
    JamKlakis = false;

}

void vortoludo::novafrazo()
{
    QString sTekstoD, sTekstoR;
    int i, iAleat2;
    for (int i = 0; i < iEk03D; i++)
        aPozicio[i] = false;
    iAleat3 = random(iEk03D);
    while (aEk03A[iAleat3])
        iAleat3 = random(iEk03D);
    if (aEk03D[iAleat3].toInt() > 0)
    {
        QList<QPushButton *> chiuj_butonoj =
                this->parentWidget()->parentWidget()->parentWidget()->findChildren<QPushButton *>(Leciono + "Button"  + aEk03D[iAleat3]);
        if (chiuj_butonoj.count() > 0)
            sTekstoD = chiuj_butonoj[0]->text();
        else
            sTekstoD = "";
    }
    else
        sTekstoD = aEk03D[iAleat3];

    QList<QLabel *> chiuj_label =
            this->parentWidget()->parentWidget()->parentWidget()->findChildren<QLabel *>(Leciono + "Label"  + aEk03R[iAleat3]);
    if (chiuj_label.count() > 0)
        sTekstoR = chiuj_label[0]->text();
    else
        sTekstoR = "";
    this->ui->Vorto->setText(sTekstoD);
    iPozicio = random(5);
    aPozicio[iAleat3] = true;
    chiuj_radioj[iPozicio]->setText(sTekstoR);
    for (i = 0; i < 5; i++)
    {
        if (i != iPozicio)
        {
            iAleat2 = random(iEk03D);
            while ( aPozicio[iAleat2])
                iAleat2 = random(iEk03D);
            aPozicio[iAleat2] = true;
            chiuj_label =
                    this->parentWidget()->parentWidget()->parentWidget()->findChildren<QLabel *>(Leciono + "Label"  + aEk03R[iAleat2]);
            if (chiuj_label.count() > 0)
                sTekstoR = chiuj_label[0]->text();
            else
                sTekstoR = "";
            chiuj_radioj[i]->setText(sTekstoR);
        }

    }
    ui->Grupo->setEnabled(true);

}

void vortoludo::on_frazo0_clicked(bool checked)
{
    if (checked)
        grupoclick(0);
}

void vortoludo::on_frazo1_clicked(bool checked)
{
    if (checked)
        grupoclick(1);
}


void vortoludo::on_frazo2_clicked(bool checked)
{
    if (checked)
        grupoclick(2);
}

void vortoludo::on_frazo3_clicked(bool checked)
{
    if (checked)
        grupoclick(3);
}

void vortoludo::on_frazo4_clicked(bool checked)
{
    if (checked)
        grupoclick(4);
}

void vortoludo::on_printilo_ps_clicked()
{
    // Uzas lokajn variablojn, por ke ili ne miksigh�u kun tiuj de la ekzerco mem
    int iAleat3, iPozicio;
    QStringList aEk03D;
    QStringList aEk03R;
    QList<bool> aPozicio;
    int     iEk03D;
    QString Leciono;
    //


    QPrinter printer2(QPrinter::HighResolution);
    printer2.setDocName(this->objectName());
    QPrintDialog *dialog = new QPrintDialog(&printer2);

    if (dialog->exec() != QDialog::Accepted)
        return;

    QString EkzercoVortoLudo = this->objectName().right(4);
    Leciono = this->objectName().left(6);
    QString LTR_Marko = QString::fromUtf8("\u200E");
    QString RTL_Marko = QString::fromUtf8("\u200F");
    QString PDF_Marko = QString::fromUtf8("\u202C");
    QString RLE_Marko = QString::fromUtf8("\u202B");
    QString LRE_Marko = QString::fromUtf8("\u202A");
    QString RLO_Marko = QString::fromUtf8("\u202E");
    QString LRO_Marko = QString::fromUtf8("\u202D");


    QString HTML_Teksto;

    HTML_Teksto.append( "<body  dir=" + Direkto + " style=\" font-family:'" );
    HTML_Teksto.append(this->parentWidget()->font().family() + "'; font-size:");
    HTML_Teksto.append( QString::number(qRound(this->parentWidget()->font().pixelSize() / 1.33333 )) + "pt; font-weight:400; font-style:normal;\">");
    HTML_Teksto.append("<P><h2>Kurso de Esperanto   -   " + this->objectName() + "   (kurso.com.br)" + LTR_Marko + "</h2></P>");
    HTML_Teksto.append("<P><B>" + this->ui->Ekz_Vort1->text() + "</B></P>");
    HTML_Teksto.append("<P>" + this->ui->Ekz_Vort2->text() + "</P><P>&nbsp;</P>");

    iEk03D = _Matriz(&aEk03D,EkzercoVortoLudo,"D");
    _Matriz(&aEk03R,EkzercoVortoLudo,"R");
    aPozicio.clear();
    for (int i = 0; i < iEk03D; i++)
    {
        aPozicio << false;
    }

    QString sTekstoD, sTekstoR;
    QList<QLabel *> chiuj_label;
    QList<QPushButton *> chiuj_butonoj;
    QString chiuj_radioj[5];
    QString Literoj[5] = {
        QString::fromUtf8("a"),
        QString::fromUtf8("b"),
        QString::fromUtf8("c"),
        QString::fromUtf8("ĉ"),
        QString::fromUtf8("d") };


    HTML_Teksto.append("<table>");

    QString HTML_Respondo = "<P dir=\"LTR\">Respondoj: <br>";
    int j, iAleat2;
    QString SubaLinio ;
    if (Direkto == "LTR")
        SubaLinio = "[&nbsp;&nbsp;]&nbsp;";
    else
        SubaLinio = "&nbsp;[&nbsp;&nbsp;]" + LTR_Marko;
    for (int i = 0; i < iEk03D; i++)
    {
        for (int k = 0; k < iEk03D; k++)
            aPozicio[k] = false;

        iAleat3 = i;

        if (aEk03D[iAleat3].toInt() > 0)
        {
            chiuj_butonoj =
                    this->parentWidget()->parentWidget()->parentWidget()->findChildren<QPushButton *>(Leciono + "Button"  + aEk03D[iAleat3]);
            if (chiuj_butonoj.count() > 0)
                sTekstoD = chiuj_butonoj[0]->text();
            else
                sTekstoD = "";
        }
        else
            sTekstoD = aEk03D[iAleat3];

        if (Direkto == "LTR")
        {
            if ( i % 2 == 0)
                HTML_Teksto.append("<tr><td><B>" + QString::number(i+1) + ") " + sTekstoD + "</B><br>");
            else
                HTML_Teksto.append(    "<td><B>" + QString::number(i+1) + ") " + sTekstoD + "</B><br>");
        }
        else
        {
            if ( i % 2 == 0)
                HTML_Teksto.append("<tr><td><B>" + sTekstoD.replace(LTR_Marko, "") + " (" + QString::number(i+1) + "</B><br>");
            else
                HTML_Teksto.append(    "<td><B>" + sTekstoD.replace(LTR_Marko, "") + " (" + QString::number(i+1) + "</B><br>");
        }


        chiuj_label =
                this->parentWidget()->parentWidget()->parentWidget()->findChildren<QLabel *>(Leciono + "Label"  + aEk03R[iAleat3]);
        if (chiuj_label.count() > 0)
            sTekstoR = chiuj_label[0]->text();
        else
            sTekstoR = "";

        iPozicio = random(5);
        aPozicio[iAleat3] = true;
        chiuj_radioj[iPozicio] = sTekstoR;
        HTML_Respondo.append(QString::number(i+1) + ")&nbsp;" + Literoj[iPozicio] + "&nbsp;&nbsp;&nbsp; ");


        for (j = 0; j < 5; j++)
        {
            if (j != iPozicio)
            {
                iAleat2 = random(iEk03D);
                while ( aPozicio[iAleat2])
                    iAleat2 = random(iEk03D);
                aPozicio[iAleat2] = true;
                chiuj_label =
                        this->parentWidget()->parentWidget()->parentWidget()->findChildren<QLabel *>(Leciono + "Label"  + aEk03R[iAleat2]);
                if (chiuj_label.count() > 0)
                    sTekstoR = chiuj_label[0]->text();
                else
                    sTekstoR = "";
                chiuj_radioj[j] = sTekstoR;
            }

        }

        for (j = 0; j < 5; j++)
        {
            if (Direkto == "LTR")
                HTML_Teksto.append( Literoj[j] + ") " + SubaLinio +  chiuj_radioj[j] + "<br>");
            else
            {
                chiuj_radioj[j].replace("(", RLO_Marko + "(" + PDF_Marko );
                chiuj_radioj[j].replace(")", RLO_Marko + ")" + PDF_Marko );
                HTML_Teksto.append(RLE_Marko +
                                   chiuj_radioj[j]  +
                                   PDF_Marko + LRE_Marko +  SubaLinio +  "(" + Literoj[j]  + PDF_Marko + "<br>");
            }
        }


        if ( i % 2 == 0)
            HTML_Teksto.append("<br></td>");
        else
            HTML_Teksto.append("<br></td></tr>");

        if ( ( i % 2 == 0) && ( i == iEk03D-1 ) )
             HTML_Teksto.append("</tr>");

    }

    HTML_Teksto.append("</table>");

    HTML_Respondo.append("</P>");
    HTML_Respondo.append("</body>");

    QTextDocument *document = new QTextDocument();
    //document->setDefaultFont(this->parentWidget()->font());
    document->setHtml(HTML_Teksto + HTML_Respondo);
    document->adjustSize();
    document->print(&printer2);

}

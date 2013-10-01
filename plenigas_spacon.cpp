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

#include "plenigas_spacon.h"
#include "ui_plenigas_spacon.h"
#include <ctime> // to use the time function
#include <cstdlib>
#include <QtGui>
#include <QtCore>
#include "funkcioj.h"
using namespace std;



plenigas_spacon::plenigas_spacon(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::plenigas_spacon)
{
    ui->setupUi(this);
    this->ui->Tajpujo->setVisible(false);
    this->ui->antauen->setVisible(false);

}

plenigas_spacon::~plenigas_spacon()
{
    delete ui;
}

void plenigas_spacon::on_BitBtn4_clicked()
{
    iAktualaPagho = 0;
    // this->ui->printilo_ps->setEnabled(false);
    sEkzerco = this->objectName().right(4);
    iEk04D =  _Matriz2(&aEk04D,sEkzerco,"D",6);
    _Matriz2(&aEk04R,sEkzerco,"R",6);
    _Matriz(&aEk04T,sEkzerco,"T");
    while (aEk04T.size() < iEk04D)
        aEk04T.append("");

    this->ui->Tajpujo->setVisible(true);
    this->ui->Tajpujo->setEnabled(true);
    this->ui->BitBtn5->setEnabled(true);
    this->ui->BitBtn4->setEnabled(false);
    this->ui->Placar25->setValue(iEk04D);
    this->ui->Placar26->setValue(0);
    this->ui->Placar27->setValue(0);
    this->ui->Placar28->setValue(0);
    iKorektaj4 = 0;
    iEraraj4 = 0;
    Atendu = false;
    //aEk04A.clear(iEk04D);
    aEk04A.clear();
    this->ui->BitBtn6->setEnabled(true);
    for ( int i=0; i < iEk04D ; i++) {
        //aEk04A[i] = false;
        aEk04A << false;
    }

    novafrazo();

}

void plenigas_spacon::on_BitBtn6_clicked()
{
    /*if (Atendu)
    {
        this->ui->BitBtn6->setVisible(true);
        this->ui->antauen->setVisible(false);
        Atendu = false;
        novafrazo();
    }
    else {*/

        QString sTeksto[5];
        sTeksto[0] = purigas(this->ui->Edit1->text(), true);
        sTeksto[1] = purigas(this->ui->Edit2->text(), true);
        sTeksto[2] = purigas(this->ui->Edit3->text(), true);
        sTeksto[3] = purigas(this->ui->Edit4->text(), true);
        sTeksto[4] = purigas(this->ui->Edit5->text(), true);

        if     ((sTeksto[0] == aEk04R[iAleat4][0]) &&
                (sTeksto[1] == aEk04R[iAleat4][1]) &&
                (sTeksto[2] == aEk04R[iAleat4][2]) &&
                (sTeksto[3] == aEk04R[iAleat4][3]) &&
                (sTeksto[4] == aEk04R[iAleat4][4]) )
        {
            iKorektaj4++;
            this->ui->Placar25->setValue(iEk04D - iKorektaj4);
            this->ui->Placar26->setValue(iKorektaj4);
            aEk04A[iAleat4] = true;
            Jes();
            Atendu = false;
        }
        else
        {
            iEraraj4++;
            this->ui->Placar27->setValue(iEraraj4);;
            Ne();
            this->ui->Edit1->setEnabled(false);
            this->ui->Edit2->setEnabled(false);
            this->ui->Edit3->setEnabled(false);
            this->ui->Edit4->setEnabled(false);
            this->ui->Edit5->setEnabled(false);
            if (sTeksto[0] != aEk04R[iAleat4][0])
                this->ui->KorektaVorto1->setVisible(true);
            if (sTeksto[1] != aEk04R[iAleat4][1])
                this->ui->KorektaVorto2->setVisible(true);
            if (sTeksto[2] != aEk04R[iAleat4][2])
                this->ui->KorektaVorto3->setVisible(true);
            if (sTeksto[3] != aEk04R[iAleat4][3])
                this->ui->KorektaVorto4->setVisible(true);
            if (sTeksto[4] != aEk04R[iAleat4][4])
                this->ui->KorektaVorto5->setVisible(true);
            Atendu = true;
            this->ui->BitBtn6->setVisible(false);
            this->ui->antauen->setVisible(true);
        }
        this->ui->Placar28->setValue((iKorektaj4 * 100)/ (iEraraj4+iKorektaj4));

        if (!Atendu)
        {
            if ( (this->ui->Placar25->value() > 0) )
                novafrazo();
            else
            {
                Mesagxo(iEraraj4, iKorektaj4);
                on_BitBtn5_clicked();
            }
        }
    //}

}

void plenigas_spacon::novafrazo()
{

    int longeco, i, interna_spaco, kiomda = 0;
    iAleat4 = random(iEk04D);
    while ( aEk04A[iAleat4] ) {
        iAleat4 = random(iEk04D);
    }

    this->ui->Vorto1->setText(aEk04D[iAleat4][0]);
    this->ui->Vorto2->setText(aEk04D[iAleat4][1]);
    this->ui->Vorto3->setText(aEk04D[iAleat4][2]);
    this->ui->Vorto4->setText(aEk04D[iAleat4][3]);
    this->ui->Vorto5->setText(aEk04D[iAleat4][4]);
    this->ui->Vorto6->setText(aEk04D[iAleat4][5]);
    this->ui->KorektaVorto1->setText(aEk04R[iAleat4][0]);
    this->ui->KorektaVorto2->setText(aEk04R[iAleat4][1]);
    this->ui->KorektaVorto3->setText(aEk04R[iAleat4][2]);
    this->ui->KorektaVorto4->setText(aEk04R[iAleat4][3]);
    this->ui->KorektaVorto5->setText(aEk04R[iAleat4][4]);
    this->ui->Traduko->setText(aEk04T[iAleat4]);

    //interna_spaco = this->ui->Edit1->textMargins().left() + 12;
    interna_spaco = this->ui->Vorto1->fontMetrics().width(" ");
    QList<QLabel *> chiuj_label = this->ui->Tajpujo->findChildren<QLabel *>();
    QList<QLineEdit *> chiuj_edit = this->ui->Tajpujo->findChildren<QLineEdit *>();
    QList<QLayout *> chiuj_layout = this->ui->Tajpujo->findChildren<QLayout *>();
    kiomda = chiuj_edit.count();
    QMargins marghenoj;
    for (i=0; (i < kiomda); i++)
    {
        if (aEk04R[iAleat4][i] != "")
        {
            longeco =  this->ui->Vorto1->fontMetrics().width(aEk04R[iAleat4][i]);
            chiuj_edit[i]->setFixedWidth(longeco + interna_spaco);
            chiuj_edit[i]->setVisible(true);
            chiuj_edit[i]->setEnabled(true);
            chiuj_label[(i*2)+1]->setVisible(false);
            if ((chiuj_label[i *2]->text().right(1) == " ") && (chiuj_label[(i * 2) +2]->text().left(1) != " ") )
            {
                chiuj_edit[i]->setAlignment(Qt::AlignRight);
                chiuj_label[(i *2)+1]->setAlignment(Qt::AlignRight);
            }
            else
            {
                chiuj_edit[i]->setAlignment(Qt::AlignLeft);
                chiuj_label[(i *2)+1]->setAlignment(Qt::AlignLeft);
            }
            marghenoj = chiuj_layout[(i*2)+2]->contentsMargins();
            if (chiuj_label[i *2]->text().right(1) == " ")
                marghenoj.setLeft(3);
            else
                marghenoj.setLeft(1);
            if (chiuj_label[(i * 2) +2]->text().left(1) == " ")
                marghenoj.setRight(3);
            else
                marghenoj.setRight(1);
            chiuj_layout[(i*2)+2]->setContentsMargins(marghenoj);
            marghenoj = chiuj_edit[i]->textMargins();
            marghenoj.setLeft(0);
            marghenoj.setRight(0);
            chiuj_edit[i]->setTextMargins(marghenoj);
            chiuj_layout[(i*2)+2]->update();
        }
        else
        {
            chiuj_edit[i]->setVisible(false);
            chiuj_label[(i*2)+1]->setVisible(false);
        }
        chiuj_edit[i]->setText("");
    }
    this->ui->Edit1->setFocus();
}


void plenigas_spacon::on_BitBtn5_clicked()
{
    this->ui->BitBtn4->setEnabled(true);
    this->ui->BitBtn5->setEnabled(false);
    this->ui->BitBtn6->setVisible(true);
    this->ui->antauen->setVisible(false);
    this->ui->BitBtn6->setEnabled(false);
    this->ui->Tajpujo->setVisible(false);
    this->ui->Traduko->setText("");
    // this->ui->printilo_ps->setEnabled(true);
    this->ui->BitBtn4->setFocus();

}


void plenigas_spacon::on_printilo_ps_clicked()
{

    // Uzas lokajn variablojn, por ke ili ne miksiĝu kun tiuj de la ekzerco mem
    QList<QStringList> aEk04D;
    QStringList aEk04T;
    QList<QStringList> aEk04R;
    int iEk04D;
    QString sEkzerco;
    //


    QPrinter printer2(QPrinter::HighResolution);
    sEkzerco = this->objectName().right(4);
    printer2.setDocName(this->objectName());
    QPrintDialog *dialog = new QPrintDialog(&printer2);

    if (dialog->exec() != QDialog::Accepted)
        return;

    QString LTR_Marko = QString::fromUtf8("\u200E");
    QString RTL_Marko = QString::fromUtf8("\u200F");
    QString PDF_Marko = QString::fromUtf8("\u202C");
    QString RLE_Marko = QString::fromUtf8("\u202B");
    QString LRE_Marko = QString::fromUtf8("\u202A");
    QString RLO_Marko = QString::fromUtf8("\u202E");
    QString LRO_Marko = QString::fromUtf8("\u202D");

    QString HTML_Teksto = "<body dir=" + Direkto + " style=\" font-family:'" ;
    HTML_Teksto.append(this->parentWidget()->font().family() + "'; font-size:");
    HTML_Teksto.append( QString::number(qRound(this->parentWidget()->font().pixelSize() / 1.33333 )) + "pt; font-weight:400; font-style:normal;\">");
    HTML_Teksto.append("<P><h2>Kurso de Esperanto   -   " + this->objectName() + "   (kurso.com.br)" + LTR_Marko + "</h2></P>");
    HTML_Teksto.append("<P><B>" + this->ui->Ekz_Plen1->text() + "</B></P>");
    HTML_Teksto.append("<P>" + this->ui->Ekz_Plen2->text() + "</P><P>&nbsp;</P>");

    iEk04D =  _Matriz2(&aEk04D,sEkzerco,"D", 6);
    _Matriz2(&aEk04R,sEkzerco,"R",6);
    _Matriz(&aEk04T,sEkzerco,"T");

    int i;
    for ( i = aEk04T.size(); i < iEk04D; i++)
        aEk04T << "";

    HTML_Teksto.append("<ol>");
    QString HTML_Respondo = "<P dir=\"ltr\">Respondoj: <br>";
    int j;
    QString SubaLinio = "__";
    for ( i = 0; i < iEk04D; i++)
    {
        HTML_Teksto.append("<li>" + aEk04T[i] + "<br>");
        HTML_Respondo.append(QString::number(i+1) + ")&nbsp;");

        if (Direkto == "RTL")
            HTML_Teksto.append(LRE_Marko);

        for (j = 0; j < 6; j++)
        {
            HTML_Teksto.append( aEk04D[i][j]  );
            if ( j < 5)
            {
                if ( aEk04D[i][j].right(1) == " "  )
                    HTML_Teksto.append("&nbsp;");

                HTML_Teksto.append( SubaLinio.repeated(aEk04R[i][j].size()));

                if (aEk04R[i][j] != "")
                    HTML_Respondo.append(aEk04R[i][j] );

                if (aEk04R[i][j+1].size() > 0)
                    HTML_Respondo.append( ",&nbsp;&nbsp;"  );

                if ( aEk04D[i][j+1].left(1) == " "  )
                    HTML_Teksto.append("&nbsp;");
            }

        }
        if (Direkto == "RTL")
            HTML_Teksto.append(PDF_Marko);


        HTML_Respondo.append( "&nbsp;&nbsp;&nbsp; "  );
        HTML_Teksto.append("<br></li>");


    }
    HTML_Teksto.append("</ol>");
    HTML_Respondo.append("</P>");
    HTML_Respondo.append("</body>");

    QTextDocument *document = new QTextDocument();
   // document->setDefaultFont(this->parentWidget()->font());
    document->setHtml(HTML_Teksto + HTML_Respondo);
    document->adjustSize();
    document->print(&printer2);
}

void plenigas_spacon::on_Edit1_returnPressed()
{
    if (this->ui->Edit2->isVisible() == true )
        this->ui->Edit2->setFocus();
    else
        on_BitBtn6_clicked();

}

void plenigas_spacon::on_Edit2_returnPressed()
{
    if (this->ui->Edit3->isVisible() == true )
        this->ui->Edit3->setFocus();
    else
        on_BitBtn6_clicked();
}

void plenigas_spacon::on_Edit3_returnPressed()
{
    if (this->ui->Edit4->isVisible() == true )
        this->ui->Edit4->setFocus();
    else
        on_BitBtn6_clicked();
}

void plenigas_spacon::on_Edit4_returnPressed()
{
    if (this->ui->Edit5->isVisible() == true )
        this->ui->Edit5->setFocus();
    else
        on_BitBtn6_clicked();
}

void plenigas_spacon::on_Edit5_returnPressed()
{
    on_BitBtn6_clicked();
}

void plenigas_spacon::on_antauen_clicked()
{
    this->ui->BitBtn6->setVisible(true);
    this->ui->antauen->setVisible(false);
    Atendu = false;
    novafrazo();
}

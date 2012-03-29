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

#include "kiomahoro.h"
#include "ui_kiomahoro.h"
#include "funkcioj.h"
#include <QtGui>
#include <QtCore>

kiomahoro::kiomahoro(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::kiomahoro)
{
    ui->setupUi(this);
}

kiomahoro::~kiomahoro()
{
    delete ui;
}

void kiomahoro::on_BitBtn1_clicked()
{
    this->ui->BitBtn1->setEnabled(false);
    this->ui->BitBtn3->setEnabled(true);
    // this->ui->printilo_ps->setEnabled(false);
    iEk01D = _Matriz(&aEk01D,"1101","D");
    _Matriz(&aEk01R,"1101","R");
    this->ui->Placar1->setValue(iEk01D);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj = 0;
    iEraraj = 0;
    this->ui->Vorto0->setText("");
    this->ui->BitBtn2->setEnabled(true);
    aEk01A.resize(iEk01D);
    for (int i = 0; i < iEk01D; i++)
        aEk01A[i] = false;
    novafrazo();

}

void kiomahoro::on_BitBtn3_clicked()
{
    this->ui->BitBtn1->setEnabled(true);
    this->ui->BitBtn3->setEnabled(false);
    this->ui->BitBtn2->setEnabled(false);
    this->ui->Vorto0->setText("");
    this->ui->Edit1->setText("");
    this->ui->Edit1->setEnabled(false);
    // this->ui->printilo_ps->setEnabled(true);
    this->ui->BitBtn1->setFocus();

}

void kiomahoro::novafrazo()
{
    iAleat1 = random(iEk01D);
    while (aEk01A[iAleat1])
        iAleat1 = random(iEk01D);
    this->ui->Vorto0->setText( aEk01D[iAleat1]);
    this->ui->Edit1->setText("");
    this->ui->Edit1->setCursorPosition(0);
    this->ui->BitBtn2->setEnabled(true);
    this->ui->Edit1->setEnabled(true);
    this->ui->Edit1->setFocus();
}



void kiomahoro::on_BitBtn2_clicked()
{
    QString sRespondo = this->ui->Edit1->text().trimmed();
    if (sRespondo != ":" )
    {

        this->ui->BitBtn2->setEnabled(false);
        this->ui->Edit1->setEnabled(false);
        if ( sRespondo == aEk01R[iAleat1] )
        {
            iKorektaj++;
            this->ui->Placar1->setValue(iEk01D - iKorektaj);
            this->ui->Placar2->setValue(iKorektaj);
            aEk01A[iAleat1] = true;
            Jes();
            //Atendu(2);
        }
        else
        {
            this->ui->BitBtn3->setEnabled(false);
            iEraraj++;
            this->ui->Placar3->setValue(iEraraj);
            Ne();
            this->ui->Korekta->setText(aEk01R[iAleat1]);

            tekstoblinko(this->ui->Korekta);

            this->ui->Korekta->setText("");
            this->ui->BitBtn3->setEnabled(true);
        }
        this->ui->Placar4->setValue((iKorektaj * 100)/(iEraraj+iKorektaj));
        if (iKorektaj < iEk01D)
            novafrazo();
        else
        {
            Mesagxo(iEraraj, iKorektaj);
            on_BitBtn3_clicked();
        }
    }
    else
        this->ui->Edit1->setFocus();
}

void kiomahoro::on_Edit1_returnPressed()
{
    on_BitBtn2_clicked();
}

void kiomahoro::on_printilo_ps_clicked()
{
    // Uzas lokajn variablojn, por ke ili ne miksiĝu kun tiuj de la ekzerco mem
    QStringList aEk01D;
    QStringList aEk01R;
    int     iEk01D;
    //


    QPrinter printer2(QPrinter::HighResolution);
    printer2.setDocName(this->objectName());
    QPrintDialog *dialog = new QPrintDialog(&printer2);

    if (dialog->exec() != QDialog::Accepted)
        return;


    QString HTML_Teksto = "<body style=\" font-family:'" ;
    HTML_Teksto.append(this->parentWidget()->font().family() + "'; font-size:");
    HTML_Teksto.append( QString::number(qRound(this->parentWidget()->font().pixelSize() / 1.33333 )) + "pt; font-weight:400; font-style:normal;\">");
    HTML_Teksto.append("<P><h2>Kurso de Esperanto   -   " + this->objectName() + "   (kurso.com.br)</h2></P>");
    HTML_Teksto.append("<P><B>" + this->ui->Lec11_Label3->text() + "</B></P>");
    HTML_Teksto.append("<P><B>" + this->ui->label->text() + "</B></P>");
    HTML_Teksto.append("<P>" + this->ui->Lec11_Label12->text() + "</P>");

    iEk01D =  _Matriz(&aEk01D, "1101","D");
    _Matriz(&aEk01R, "1101", "R");
    HTML_Teksto.append("<ol>");
    QString HTML_Respondo = "<P>Respondoj: <br>";
    QString SubaLinio = "______:______";
    for (int i = 0; i < iEk01D; i++)
    {
        HTML_Teksto.append("<li>" + aEk01D[i] + " : " + SubaLinio + "<br></li>");
        HTML_Respondo.append(QString::number(i+1) + ")&nbsp;");
        HTML_Respondo.append(aEk01R[i] + "&nbsp;&nbsp;&nbsp; ");
    }
    HTML_Teksto.append("</ol>");
    HTML_Respondo.append("</P>");
    HTML_Respondo.append("</body>");

    QTextDocument *document = new QTextDocument();
//    document->setDefaultFont(this->parentWidget()->font());
    document->setHtml(HTML_Teksto + HTML_Respondo);
    document->adjustSize();
    document->print(&printer2);

}

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

#include "cx_edit.h"

cx_edit::cx_edit(QWidget *parent) :
    QLineEdit(parent)
{
}

void cx_edit::keyPressEvent(QKeyEvent *event)
{
    if ( (event->key() == Qt::Key_X) && (lCxapeligo))
    {
        int arg1 = this->cursorPosition()-1;
        QByteArray antaualitero = (this->text().mid(arg1,1)).toAscii();
        QString novalitero;
        switch (antaualitero[0]) {
        case 'c':
            novalitero = QString::fromUtf8("ĉ");
            break;
        case 'C':
            novalitero = QString::fromUtf8("Ĉ");
            break;
        case 'g':
            novalitero = QString::fromUtf8("ĝ");
            break;
        case 'G':
            novalitero = QString::fromUtf8("Ĝ");
            break;
        case 'h':
            novalitero = QString::fromUtf8("ĥ");
            break;
        case 'H':
            novalitero = QString::fromUtf8("Ĥ");
            break;
        case 'j':
            novalitero = QString::fromUtf8("ĵ");
            break;
        case 'J':
            novalitero = QString::fromUtf8("Ĵ");
            break;
        case 's':
            novalitero = QString::fromUtf8("ŝ");
            break;
        case 'S':
            novalitero = QString::fromUtf8("Ŝ");
            break;
        case 'u':
            novalitero = QString::fromUtf8("ŭ");
            break;
        case 'U':
            novalitero = QString::fromUtf8("Ŭ");
            break;
        default:
            novalitero = "";

        }
        if (novalitero != ""){
            this->setSelection(arg1, 1);
            this->insert(novalitero);
        }
        else
            QLineEdit::keyPressEvent(event);


    }
    else
        QLineEdit::keyPressEvent(event);

}


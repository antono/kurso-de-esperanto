#ifndef PRONONCO_H
#define PRONONCO_H

#include <QFrame>
#include "QtMultimedia/qaudioformat.h"
#include "QtMultimedia/qaudioinput.h"
#include "QtMultimedia/qaudiooutput.h"
#include <QFile>
#include <phonon/mediaobject.h>

namespace Ui {
    class prononco;
}

class prononco : public QFrame
{
    Q_OBJECT

public:
    explicit prononco(QWidget *parent = 0);
    ~prononco();

private slots:
    void on_PP_Startu_clicked();

    void novafrazo();

    void RegistrasVocxon();

    void on_PP_Haltu_clicked();

    void on_PP_Antauen_clicked();

    void on_PP_Mik_re_clicked();

    void on_PP_Aud_re_clicked();

    void LudoFinita(QAudio::State);

    void ChesasRegistri();

    void LudasRegistrita(int);

    void Registru(int);

    void Progreso();


private:
    Ui::prononco *ui;

    QStringList aEk09D;
    QString aEk09T[4][2];
    int     aEk09F[4];

    QList<bool> aEk09A;

    int iAleat9, iEk09D, Kiome, KiomFoje, RegistraLongo;
    QFile SonDosiero;   // class member.
    QAudioInput* audio_enen; // class member.
    QAudioFormat formato;
    QAudioOutput* audio_eksteren;
    Phonon::MediaObject *ludilo;
    QString Provizorujo;

};

#endif // PRONONCO_H

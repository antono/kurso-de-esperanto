#ifndef MP3LUDILO_H
#define MP3LUDILO_H

#include <QFrame>
#include <phonon/mediaobject.h>


namespace Ui {
    class mp3ludilo;
}

class mp3ludilo : public QFrame
{
    Q_OBJECT

public:
    explicit mp3ludilo(QWidget *parent = 0);
    ~mp3ludilo();

private slots:
    void on_Ludu_clicked();
    void on_Chesu_clicked();
    void on_Pauzu_clicked();
    void PaghoShanghita(int);

private:
    Ui::mp3ludilo *ui;
    Phonon::MediaObject *ludilo;
    int MiaPagho;

};

#endif // MP3LUDILO_H

#ifndef VIDEOLUDILO_H
#define VIDEOLUDILO_H

#include <QFrame>
#include <phonon/videoplayer.h>
#include <QVBoxLayout>
#include <QHBoxLayout>


namespace Ui {
class videoludilo;
}

class videoludilo : public QFrame
{
    Q_OBJECT
    
public:
    explicit videoludilo(QWidget *parent = 0);
    ~videoludilo();
    
private:
    Ui::videoludilo *ui;
    Phonon::VideoPlayer *videoLudilo;
    QVBoxLayout layout;
    QHBoxLayout layoutH;
    int MiaPagho;


private slots:
    void onPlay();
    void onStop();
    void on_Pauzu_clicked();
    void PaghoShanghita(int);

};

#endif // VIDEOLUDILO_H

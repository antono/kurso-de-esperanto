#ifndef AUDKOMPRENO_H
#define AUDKOMPRENO_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>

namespace Ui {
    class audkompreno;
}

class audkompreno : public QFrame
{
    Q_OBJECT

public:
    explicit audkompreno(QWidget *parent = 0);
    ~audkompreno();

private slots:
    void on_BitBtn8_clicked();
    void novavorto();
    void analizu();

    void on_BitBtn10_clicked();

    void on_BitBtn9_clicked();


    void on_Edit1_returnPressed();

private:
    Ui::audkompreno *ui;
    QList<QLabel *> chiuj_label;
    QList<QPushButton *> chiuj_butonoj;

    QString EkzercoAudado;
    int iEk02D;

    QList<bool> aEk02A;

    QStringList aEk02D;
    int iKorektaj2;
    int iEraraj2;
    int iAleat2;
    QString sMp3dos, Leciono, LTR_Marko;

};

#endif // AUDKOMPRENO_H

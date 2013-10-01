#ifndef EKZERCO1_H
#define EKZERCO1_H

#include <QFrame>
#include <QPushButton>

namespace Ui {
    class ekzerco1;
}

class ekzerco1 : public QFrame
{
    Q_OBJECT

public:
    explicit ekzerco1(QWidget *parent = 0);
    ~ekzerco1();

private slots:

    void novafrazo();
    void novavorto();
    void vortoklako(int klakita);

    void on_BitBtn3_clicked();

    void on_BitBtn2_clicked();

    void on_BitBtn1_clicked();

    void on_butono0_clicked();

    void on_butono1_clicked();

    void on_butono2_clicked();

    void on_butono3_clicked();

    void on_butono4_clicked();

    void on_butono5_clicked();

private:
    Ui::ekzerco1 *ui;

    int iEk01D, iKorektaj, iEraraj, iAleat1;
    QString sMp3dos;
    bool JamKlakis, lNovaFrazo;
    QStringList aEk01D;
    QList<bool> aEk01A;
    bool aFrazoElek[6];
    int Selektitaj[4];
    int PozicioSelektitaj[4];
    int Hazardaj[2];
    QList<QPushButton *> chiuj_butonoj;
};

#endif // EKZERCO1_H

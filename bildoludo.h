#ifndef BILDOLUDO_H
#define BILDOLUDO_H

#include <QtGui>
#include <QtCore>
#include <mylabel.h>

namespace Ui {
    class bildoludo;
}

class bildoludo : public QFrame
{
    Q_OBJECT

public:
    explicit bildoludo(QWidget *parent = 0);
    ~bildoludo();

private slots:
    void on_BildoListo_activated(const QString &arg1);

    void novafrazo();

    void Malaperigu();

    void demandas();

    void bildoklako(int);

    void bildoblinko(int);

    void tekstoblinko();

    int Matrico(const QString);

    void on_BitBtn5_clicked();

    void on_Butono_clicked();

    void on_Image1_clicked();

    void on_Image2_clicked();

    void on_Image3_clicked();

    void on_Image4_clicked();

    void on_Image5_clicked();

    void on_Tajpado_returnPressed();

    void on_stilo_muso_clicked();

    void on_BitBtn4_clicked();

private:
    Ui::bildoludo *ui;

    int iKorektaj3, iEraraj3, iAleat3, iPozicio;

    std::vector<bool> aEk03A;

    QStringList aEk03R;
    int iEk03D;
    QStringList Listo;
    QFileInfoList Dosieroj;
    bool JamKlakis;
    int iAleat2;

    std::vector<bool> aPozicio;

    int Lotumitaj[5], Lotumitaj2[5], Lotumitaj3[5];

    QList<QLabel *> chiuj_bildoj;
    QList<QLabel *> chiuj_tekstoj;

};

#endif // BILDOLUDO_H

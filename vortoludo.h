#ifndef VORTOLUDO_H
#define VORTOLUDO_H

#include <QFrame>
#include <QRadioButton>

namespace Ui {
    class vortoludo;
}

class vortoludo : public QFrame
{
    Q_OBJECT

public:
    explicit vortoludo(QWidget *parent = 0);
    ~vortoludo();

private slots:
    void on_BitBtn18_clicked();
    void novafrazo();
    void grupoclick(int klakita);
    void on_BitBtn20_clicked();

    void on_frazo0_clicked(bool checked);

    void on_frazo1_clicked(bool checked);

    void on_frazo2_clicked(bool checked);

    void on_frazo3_clicked(bool checked);

    void on_frazo4_clicked(bool checked);

    void on_printilo_ps_clicked();

private:
    Ui::vortoludo *ui;

    int iKorektaj3, iEraraj3, iAleat3, iPozicio;
    QStringList aEk03D;
    QStringList aEk03R;
    QList<bool> aEk03A;
    QList<bool> aPozicio;


    int     iEk03D;
    int iAktualaPagho;
    QList<QRadioButton *> chiuj_radioj;
    QString Leciono;
    bool    JamKlakis;
};

#endif // VORTOLUDO_H

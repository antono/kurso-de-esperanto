#ifndef EKZNUMERALOJ_H
#define EKZNUMERALOJ_H

#include <QFrame>

namespace Ui {
    class ekznumeraloj;
}

class ekznumeraloj : public QFrame
{
    Q_OBJECT

public:
    explicit ekznumeraloj(QWidget *parent = 0);
    ~ekznumeraloj();

private slots:
    void on_BitBtn1_clicked();

    void novafrazo();

    void on_BitBtn3_clicked();

    void on_BitBtn2_clicked();

    void on_Edit1_returnPressed();

    void on_printilo_ps_clicked();

private:
    Ui::ekznumeraloj *ui;

    int iKorektaj, iEraraj, iAleat1;
    QStringList aEk01D;
    QStringList aEk01R;

    QList<bool> aEk01A;

    int     iEk01D;

};

#endif // EKZNUMERALOJ_H

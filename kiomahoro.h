#ifndef KIOMAHORO_H
#define KIOMAHORO_H

#include <QFrame>

namespace Ui {
    class kiomahoro;
}

class kiomahoro : public QFrame
{
    Q_OBJECT

public:
    explicit kiomahoro(QWidget *parent = 0);
    ~kiomahoro();

private slots:
    void on_BitBtn1_clicked();

    void novafrazo();

    void on_BitBtn3_clicked();

    void on_BitBtn2_clicked();

    void on_Edit1_returnPressed();

    void on_printilo_ps_clicked();

private:
    Ui::kiomahoro *ui;

    int iKorektaj, iEraraj, iAleat1;
    QStringList aEk01D;
    QStringList aEk01R;
    QList<bool> aEk01A;

    int     iEk01D;

};

#endif // KIOMAHORO_H

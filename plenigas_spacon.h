#ifndef PLENIGAS_SPACON_H
#define PLENIGAS_SPACON_H

#include <QFrame>

namespace Ui {
    class plenigas_spacon;
}

class plenigas_spacon : public QFrame
{
    Q_OBJECT

public:
    explicit plenigas_spacon(QWidget *parent = 0);
    ~plenigas_spacon();

private slots:
    void on_BitBtn4_clicked();

    void on_BitBtn6_clicked();

    void novafrazo();

    void on_BitBtn5_clicked();

    void on_printilo_ps_clicked();

    void on_Edit1_returnPressed();

    void on_Edit2_returnPressed();

    void on_Edit3_returnPressed();

    void on_Edit4_returnPressed();

    void on_Edit5_returnPressed();

    void on_antauen_clicked();

private:
    Ui::plenigas_spacon *ui;

    QList<QStringList> aEk04D;
    QStringList aEk04T;
    QList<QStringList> aEk04R;
    QList<bool> aEk04A;
    int iKorektaj4, iEraraj4, iAleat4, iAktualaPagho, iEk04D;
    QString sEkzerco;
    bool    Atendu;

};

#endif // PLENIGAS_SPACON_H

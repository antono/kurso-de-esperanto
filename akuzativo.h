#ifndef AKUZATIVO_H
#define AKUZATIVO_H

#include <QFrame>
#include <QLabel>
#include <QTimer>

namespace Ui {
    class akuzativo;
}

class akuzativo : public QFrame
{
    Q_OBJECT

public:
    explicit akuzativo(QWidget *parent = 0);
    ~akuzativo();

private slots:
    void on_BitBtn1_clicked();
    void novafrazo();
    void vortoklako(int klakita);
    void tekstoblinko();

    void on_BitBtn3_clicked();

    void on_BitBtn2_clicked();

    void on_label_164_clicked();

    void on_label_165_clicked();

    void on_label_166_clicked();

    void on_label_167_clicked();

    void on_label_168_clicked();

    void on_label_169_clicked();

    void on_label_170_clicked();

    void on_label_171_clicked();

    void on_label_172_clicked();

    void on_label_173_clicked();

private:
    Ui::akuzativo *ui;

    int iAleat2, iKorektaj, iEraraj;

    QList<QStringList> aEk02D;
    QList<QStringList> aEk02R;
    QList<QStringList> aEk02K;
    QList<bool>        aEk02A;
    QStringList              aEk02T;
    QStringList              Klarigoj;

    QString aFrazoElek[11];
    int     iEk02D;
    QList<QLabel *> chiuj_label;
};

#endif // AKUZATIVO_H

#ifndef TRADUKO_H
#define TRADUKO_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class traduko;
}

class traduko : public QDialog
{
    Q_OBJECT
    
public:
    explicit traduko(QWidget *parent = 0);
    ~traduko();
    

signals:
    void novapagho(QString pagho);
    void novafrazo(QString pagho, QString frazo);


private slots:

    void closeEvent(QCloseEvent *event);

    void on_literGrando_valueChanged(int arg1);

    void on_tiparo_currentIndexChanged(const QString &arg1);

    void konfiguro();

    void ListigasLingvojn();

    void SharghasTrad(QString Sekcio);

    void Movighas(QString Direkto);


    void on_Button5_clicked();

    void on_Button1_clicked();

    void on_Button6_clicked();

    void on_Button2_clicked();

    void on_Listo_activated(const QString &arg1);

    void on_lingvoj1_activated(int index);

    bool SavasTrad();

    void on_lingvoj2_activated(int index);

    void on_Button4_clicked();

    QStringList Ordigas(QString Sekcio);

    void lokigas_paghotrad(QString novapagho);

    void lokigas_frazotrad(QString novafrazo);

    void showEvent(QShowEvent *);

    void on_pushButton_clicked();

private:
    Ui::traduko *ui;

    QString sTradukoDosiero, sTradukinto, Referenca1, Referenca2, aktualaSekcio, Dosierujo;

    int iLiterGrando, Leciono, Pozicio, NunaPozicio;

    QList<QStringList> LingvoListo;

    QStringList Ref1_itemoj, Ref2_itemoj, Celo_itemoj, linioj;

};

#endif // TRADUKO_H

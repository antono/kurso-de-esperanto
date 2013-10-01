#ifndef KURSO_H
#define KURSO_H

#include <QMainWindow>
#include <phonon/mediaobject.h>
#include <traduko.h>
#include <QLabel>

namespace Ui {
    class kurso;
}

class kurso : public QMainWindow
{
    Q_OBJECT

public:
    explicit kurso(QWidget *parent = 0);
    ~kurso();
    Phonon::MediaObject *ludilo;

public slots:
    void Saluton();

private slots:

    void Centrigas_Fenestron();
    void Ghustigas_fenestron();
    void ReGrandigas_Fenestron();
    void Traduku();
    void ListigasLingvojn();
    void Konfiguru();
    void komencakonfiguro();
    void SavasKonfig();
    void Stilo();
    void Fenestra_Stilo();
    void Malgrandigas();
    void ShanghasTiparon();
    void ShanghasTiparStilon();

    void closeEvent(QCloseEvent *event);
    void showEvent ( QShowEvent * event ) ;
    void keyPressEvent(QKeyEvent *);

    void on_Hejmo_clicked();

    void on_Sendas_clicked();

    void on_printilo_clicked();

    void on_Cxapeligo_toggled(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_Lingvo_activated(int index);

    void on_KieButono_clicked();

    void on_Tiparo_currentIndexChanged(const QString &arg1);

    void lokigas_paghotrad(QString novapagho);

    void lokigas_frazotrad(QString novapagho, QString novafrazo);


    /* CHI TIU PARTO ENIROS EN ESTONTA VERSIO
    void on_BildoLudo_clicked();
    */

    void on_Konfigurado_clicked();

    void on_KioEstas_clicked();

    void on_KielUzi_clicked();

    void on_Kreditoj_clicked();

    void on_Parolo_toggled(bool checked);

    void on_Noteto_toggled(bool checked);

    void on_LiterGrando_valueChanged(int arg1);


    void ShanghasPaghon(QString Nomo);

    void paghoshanghita(QWidget *arg1);
    void on_Lec01_currentChanged(QWidget *arg1);
    void on_Lec02_currentChanged(QWidget *arg1);
    void on_Lec03_currentChanged(QWidget *arg1);
    void on_Lec04_currentChanged(QWidget *arg1);
    void on_Lec05_currentChanged(QWidget *arg1);
    void on_Lec06_currentChanged(QWidget *arg1);
    void on_Lec07_currentChanged(QWidget *arg1);
    void on_Lec08_currentChanged(QWidget *arg1);
    void on_Lec09_currentChanged(QWidget *arg1);
    void on_Lec10_currentChanged(QWidget *arg1);
    void on_Lec11_currentChanged(QWidget *arg1);
    void on_Lec12_currentChanged(QWidget *arg1);
    void on_Lec13_currentChanged(QWidget *arg1);

    void on_Leciono1_clicked();
    void on_Leciono2_clicked();
    void on_Leciono3_clicked();
    void on_Leciono4_clicked();
    void on_Leciono5_clicked();
    void on_Leciono6_clicked();
    void on_Leciono7_clicked();
    void on_Leciono8_clicked();
    void on_Leciono9_clicked();
    void on_Leciono10_clicked();
    void on_Leciono11_clicked();
    void on_Leciono12_clicked();
    void on_Leciono13_clicked();


    void on_checkBox_clicked(bool checked);


    void on_butono_stilo_clicked();


    //void on_butono_listo_clicked();

    void on_TiparoEo_currentIndexChanged(const QString &arg1);

    void on_LiterGrandoEo_valueChanged(int arg1);

    void listigas_trad();

private:
    Ui::kurso *ui;

    traduko *tradukilo;

    QList<QStringList> LingvoListo;


    int alteco_originala, largheco_originala, alteco_maksimuma, largheco_maksimuma;
    bool Eta_Fenestro, Malalta_Fenestro, JamMontrita;

    QLabel * antaua;

};

#endif // KURSO_H

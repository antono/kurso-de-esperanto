#ifndef LINGVOELEKTO_H
#define LINGVOELEKTO_H

#include <QDialog>
#include <QtCore>

namespace Ui {
    class lingvoelekto;
}

class lingvoelekto : public QDialog
{
    Q_OBJECT

public:
    explicit lingvoelekto(QWidget *parent = 0);
    ~lingvoelekto();

private slots:
    void komencas();

    void on_pushButton_clicked();

    void closeEvent(QCloseEvent *event);

    void showEvent ( QShowEvent * event ) ;


private:
    Ui::lingvoelekto *ui;

    QList<QStringList> LingvoListo;
    //QList<QString> LingvoNomoj;
    //QList<QString> LingvoDosieroj;
};

#endif // LINGVOELEKTO_H

#ifndef FUNKCIOJ_H
#define FUNKCIOJ_H
#include <QSettings>
#include <QTabWidget>
#include <QProgressBar>

int random(int limo);
int  _Matriz2(QList<QStringList> * Mat, QString ek, QString tipo, int minimuma);
int  _Matriz(QStringList * Mat, QString ek, QString tipo);
void Pauzu(int sekundoj);
QString CxSist(QString frazo, int iSistemo);
void randomize();
QString purigas(QString teksto, bool minuskle);
void Ne();
void Jes();
void Noteto(bool);
void Mesagxo(int iEraraj, int iKorektaj);
void Sinkronigu();
void Trad(QWidget * Pagxaro, QString Patro);
void Sendas(QWidget * Pagxo, int PagxoNumero);
// void Saluton();
void Adiau();
void SavasEk(QTabWidget * Pagxaro);
void SxargxasEk(QTabWidget * Pagxaro, bool);
void Sendas_Printilo(QTabWidget * Pagxaro, QString Patro, QProgressBar * prog_printilo);
void mp3(QString Dosiero);
void tekstoblinko(QWidget * korekta);
QString helpdosiero(QString);

#ifdef Q_WS_X11
const QString mp3_finajho=".ogg";
const QString video_finajho=".ogv";
#endif
#ifdef Q_WS_WIN
const QString mp3_finajho=".wma";
const QString video_finajho=".wmv";
#endif
#ifdef Q_WS_MACX
const QString mp3_finajho=".mp3";
const QString video_finajho=".mov";
#endif



// eksteraj variabloj, uzotaj dum la tuta programo
extern int NumSec;
extern int Ofteco;
extern QSettings Konfiguro;
extern QSettings Tradukado;
extern QString sLingvo, sTiparo, sTiparoEo, sTradukoDosiero, sKorNomo, sKorAdreso, EkzercoAkuzativoTrad;
extern int iSistemo, LastaLeciono, LastaPagxo, iLastaFojo, iLiterGrando, iLiterGrandoEo, iFenestraStilo;
extern bool lKorektanto, lCxapeligo, Tradukilo, NeEkzistasTraduko, lSxaltilo, lNoteto;
extern QString sTradukinto;
extern QString Loko;
extern QString Direkto;


// eksteraj varibloj, uzotaj por komunikighi kun la uzulo
extern QString  smRekomencu,
                smGratulon,
                smDenove,
                smModifis,
                smTondujo,
                smDevasHaviKor,
                smDevasSavi,
                smKoverto,
                smDisketo,
                smPordo,
                smLigilo,
                // smNePasvorto
                Antauen,
                Nuligi,
                smNeSono;



#endif // FUNKCIOJ_H

#ifndef SLEEPER_H
#define SLEEPER_H

#include <QThread>

class Sleeper : public QThread
{
    Q_OBJECT
public:
    explicit Sleeper(QObject *parent = 0);
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}

signals:

public slots:

};

#endif // SLEEPER_H

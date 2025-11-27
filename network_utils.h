#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <QObject>
#include <QProcess>
#include <QRunnable>
#include <QThreadPool>
#include <QProcess>
#include <QDebug>
#include <QWidget>

class Ping
{
public:
    Ping(){

    }
    ~Ping(){}
    bool pingHost(const QString &ip);
};

class network_utils;

class PingTask : public QRunnable {
public:
    PingTask(const QString & ip,QObject * receiver):ip_(ip),receiver_(receiver){

    }

    ~PingTask(){}

    void run() override;

private:
    QString ip_;
    QObject * receiver_;
};


class network_utils : public QObject{
    Q_OBJECT
public:
        // pool_.setMaxThreadCount(10);
    network_utils(QObject * parent = nullptr):QObject(parent){}
    virtual ~network_utils(){}

    void scanRange(const QString&ip,int start,int end);

signals:
    void hostOnline(const QString&ip);

private:
    QThreadPool pool_;

};

class FUCK : public QWidget
{
    Q_OBJECT
public:
    FUCK(QWidget * parent):QWidget(parent) {}
};


#endif // NETWORK_UTILS_H

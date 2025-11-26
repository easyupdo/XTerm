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
    bool pingHost(const QString &ip){
        QProcess process;
        QString cmd;
        QStringList args;
        cmd = "ping";
        args << "-c" << "1"<<"-W"<<"3"<<ip;


        process.start(cmd,args);
        process.waitForFinished(500);
        if(process.exitCode() == 0){
            qDebug()<<"ip:"<<ip <<" Exit";
            QString output = process.readAllStandardOutput();
            if(output.contains("TTL=")||output.contains("ttl=")|| output.contains("bytes from")){
                return true;
            }
        }
        return false;
    }
};

class PingTask : public QRunnable {
public:
    PingTask(const QString & ip,QObject * receiver):ip_(ip),receiver_(receiver){

    }

    ~PingTask(){}

    void run() override{
        Ping nu;
        bool online = nu.pingHost(ip_);
        qDebug()<<"ip"<<ip_<<"run over online:"<<online;
        if(online && receiver_){
            //
            QMetaObject::invokeMethod(receiver_,"hostOnline",Qt::QueuedConnection,Q_ARG(QString,ip_));
        }
    }

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

    void scanRange(const QString&ip,int start,int end){

        for(int i = start;i<end;i++){
            QString _ip = QString("%1.%2").arg(ip).arg(i);
            qDebug()<<"BaseIP:"<<_ip;
            PingTask * task = new PingTask(_ip,this);
            pool_.start(task);
        }
        pool_.waitForDone();
    }

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

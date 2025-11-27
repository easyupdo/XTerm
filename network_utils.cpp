#include "network_utils.h"



void PingTask::run(){
    Ping nu;
    bool online = nu.pingHost(ip_);
    if(online && receiver_){
        //
        QMetaObject::invokeMethod(receiver_,"hostOnline",Qt::QueuedConnection,Q_ARG(QString,ip_));
        // network_utils * obj = qobject_cast<network_utils*>(receiver_);
        // emit obj->hostOnline(ip_);
    }
}



void network_utils::scanRange(const QString&ip,int start,int end){

    for(int i = start;i<end;i++){
        QString _ip = QString("%1.%2").arg(ip).arg(i);
        PingTask * task = new PingTask(_ip,this);
        pool_.start(task);
    }
    pool_.waitForDone();
    emit scanFinished();
}


bool Ping::pingHost(const QString &ip){
    QProcess process;
    QString cmd;
    QStringList args;
    cmd = "ping";
#ifdef Q_OS_LINUX
    args << "-c" << "1"<<"-W"<<"3"<<ip;
#else
    args << "-n" << "1"<<"-w"<<"3"<<ip;
#endif

    process.start(cmd,args);
    process.waitForFinished(500);
    if(process.exitCode() == 0){
        QString output = process.readAllStandardOutput();
        if(output.contains("TTL=")||output.contains("ttl=")|| output.contains("bytes from")){
            return true;
        }
    }
    return false;
}

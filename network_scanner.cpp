#include "network_scanner.h"
#include "ui_network_scanner.h"
#include <QTableWidgetItem>
network_scanner::network_scanner(QWidget *parent)
    : QWidget(parent)
    ,new_online_ips_ptr_(&first_container_)
    ,last_online_ips_ptr_(&second_container_)
    , ui(new Ui::network_scanner)
{
    ui->setupUi(this);
    connect(&scan_timer_,&QTimer::timeout,this,&network_scanner::on_pushButton_clicked);
    system_tray_.setToolTip("sys");
    QMenu * menu = new QMenu();
    QAction * a1 = menu->addAction("info");
    system_tray_.setContextMenu(menu);
    system_tray_.show();
    network_util_ = new network_utils();
    connect(network_util_,&network_utils::hostOnline,this,&network_scanner::resultHostOnline,Qt::QueuedConnection);
    system_tray_.showMessage("Hello","DDDD");

    // scan over
    connect(network_util_,&network_utils::scanFinished,this,&network_scanner::on_scanFinished);
}

network_scanner::~network_scanner()
{
    delete ui;
}

void network_scanner::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked() && !scan_timer_.isActive()){
        scan_timer_.setInterval(10000);
        scan_timer_.start();
        qDebug()<<" ################################timer start";
    }

    QString base_ip = QString("%1.%2.%3").arg(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text());
    int start = ui->lineEdit_4->text().toInt();
    int end = ui->lineEdit_5->text().toInt();
    network_util_->scanRange(base_ip,start,end);

}

void network_scanner::resultHostOnline(const QString&ip)
{
    qDebug()<<"IP:"<<ip<<" Online";
    if(last_online_ips_ptr_->contains(ip)){
        last_online_ips_ptr_->removeOne(ip);
    }else {
        // 新上线
        system_tray_.showMessage("online",ip);
    }
    // 添加
    new_online_ips_ptr_->append(ip);

    int current_index = ui->tableWidget->rowCount();
    qDebug()<<"current_index"<<current_index;
    ui->tableWidget->setRowCount(current_index+1);
    ui->tableWidget->setItem(current_index,0,new QTableWidgetItem(ip));
    ui->tableWidget->update();

}

void network_scanner::on_scanFinished(){
    mx_.lock();
    qDebug()<<"##### 扫描完成";
    // 掉线
    qDebug()<<">>>>>>>>>>>>>>>>LAST SIZE:"<<last_online_ips_ptr_->size() << " NEW SIZE:"<< new_online_ips_ptr_->size();
    for(auto it = last_online_ips_ptr_->begin();it != last_online_ips_ptr_->end();it++) {
        system_tray_.showMessage("offline",*it);
        qDebug()<<"REMOVE";
    }
    last_online_ips_ptr_->clear();

    QLinkedList<QString> * tmp = new_online_ips_ptr_;
    new_online_ips_ptr_ = last_online_ips_ptr_;
    last_online_ips_ptr_ = tmp;

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    mx_.unlock();
}


void network_scanner::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::CheckState::Unchecked){
        if(scan_timer_.isActive()){
            scan_timer_.stop();
        }
    }
}


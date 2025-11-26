#include "network_scanner.h"
#include "ui_network_scanner.h"
#include <QTableWidgetItem>
network_scanner::network_scanner(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::network_scanner)
{
    ui->setupUi(this);
    network_util_ = new network_utils();
    connect(network_util_,&network_utils::hostOnline,this,&network_scanner::resultHostOnline,Qt::QueuedConnection);
}

network_scanner::~network_scanner()
{
    delete ui;
}

void network_scanner::on_pushButton_clicked()
{
    QString base_ip = QString("%1.%2.%3").arg(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text());
    int start = ui->lineEdit_4->text().toInt();
    int end = ui->lineEdit_5->text().toInt();
    network_util_->scanRange(base_ip,start,end);

}

void network_scanner::resultHostOnline(const QString&ip)
{
    qDebug()<<"IP:"<<ip<<" Online";
    int current_index = ui->tableWidget->rowCount();
    qDebug()<<"current_index"<<current_index;
    ui->tableWidget->setRowCount(current_index+1);
    ui->tableWidget->setItem(current_index,0,new QTableWidgetItem(ip));
}

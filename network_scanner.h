#ifndef NETWORK_SCANNER_H
#define NETWORK_SCANNER_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "network_utils.h"
#include <QMenu>
#include <QTimer>
#include <QLinkedList>
#include <QMutex>
namespace Ui {
class network_scanner;
}

class network_scanner : public QWidget
{
    Q_OBJECT

public:
    explicit network_scanner(QWidget *parent = nullptr);
    ~network_scanner();

private slots:
    void on_pushButton_clicked();
    void on_checkBox_stateChanged(int arg1);

public slots:
    void resultHostOnline(const QString&ip);
    void on_scanFinished();

private:
    Ui::network_scanner *ui;
    network_utils *network_util_;
    QSystemTrayIcon system_tray_;
    QTimer scan_timer_;

    QMutex mx_;

    QLinkedList<QString> first_container_;
    QLinkedList<QString>  second_container_;
    QLinkedList<QString> * new_online_ips_ptr_;
    QLinkedList<QString> * last_online_ips_ptr_;
};

#endif // NETWORK_SCANNER_H

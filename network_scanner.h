#ifndef NETWORK_SCANNER_H
#define NETWORK_SCANNER_H

#include <QWidget>
#include "network_utils.h"

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

public slots:
    void resultHostOnline(const QString&ip);

private:
    Ui::network_scanner *ui;
    network_utils *network_util_;
};

#endif // NETWORK_SCANNER_H

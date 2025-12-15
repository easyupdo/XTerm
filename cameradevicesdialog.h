#ifndef CAMERADEVICESDIALOG_H
#define CAMERADEVICESDIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraInfo>
namespace Ui {
class CameraDevicesDialog;
}

class CameraDevicesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraDevicesDialog(QWidget *parent = nullptr);
    ~CameraDevicesDialog();
    void setAvaliableDevices(QList<QCameraInfo>& cameras);

    QString selectDevice();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CameraDevicesDialog *ui;
    QCameraInfo camera_info_;
    QString current_device_;
};

#endif // CAMERADEVICESDIALOG_H

#include "cameradevicesdialog.h"
#include "ui_cameradevicesdialog.h"

CameraDevicesDialog::CameraDevicesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CameraDevicesDialog)
{
    ui->setupUi(this);


}

CameraDevicesDialog::~CameraDevicesDialog()
{
    delete ui;
}

void CameraDevicesDialog::setAvaliableDevices(QList<QCameraInfo>& cameras) {
    QStringList _cameras;
    for(auto & cam:cameras){
        _cameras.append(cam.deviceName());
    }

    ui->comboBox->addItems(_cameras);
}

QString CameraDevicesDialog::selectDevice(){
    return ui->comboBox->currentText();
}

void CameraDevicesDialog::on_buttonBox_accepted()
{
    current_device_ = ui->comboBox->currentText();
    qDebug()<<"选择cam:"<<current_device_;
}


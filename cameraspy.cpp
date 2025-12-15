#include "cameraspy.h"
#include "ui_cameraspy.h"


CameraSpy::CameraSpy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraSpy)
{
    ui->setupUi(this);
    ui->mdiArea->tileSubWindows();
    // cam_ = new QCamera();
    // view_ = new QCameraViewfinder();
    // cam_.setViewfinder(view_);
    // ui->widget->layout()->addWidget(cam_);
}

CameraSpy::~CameraSpy()
{
    delete ui;
}
// Add
void CameraSpy::on_actionA_triggered()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    dialog_.setAvaliableDevices(cameras);
    dialog_.exec();
    qDebug()<<"Add:"<<dialog_.selectDevice();
    cam_ = new QCamera(dialog_.selectDevice().toLocal8Bit());
    cam_->setViewfinder(&view_);
    cam_->start();
    // ui->mdiArea->layout()->addWidget(&view_);
    ui->subwindow->layout()->addWidget(&view_);
    // ui->widget->layout()->addWidget(&view_);
}


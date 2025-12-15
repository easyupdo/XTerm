#ifndef CAMERASPY_H
#define CAMERASPY_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include "cameradevicesdialog.h"
namespace Ui {
class CameraSpy;
}

class CameraSpy : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraSpy(QWidget *parent = nullptr);
    ~CameraSpy();

private slots:
    void on_actionA_triggered();

private:
    Ui::CameraSpy *ui;
    QCamera * cam_;
    QCameraViewfinder view_;
    CameraDevicesDialog dialog_;
};

#endif // CAMERASPY_H

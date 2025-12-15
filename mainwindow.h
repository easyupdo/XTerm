#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNetwork_Scanner_triggered();

    void on_actionEditor_triggered();

    void on_actionSystem_Designer_triggered();

    void on_actionCamera_Spy_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

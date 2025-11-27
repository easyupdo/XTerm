#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "./network_scanner.h"
#include "./editor.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNetwork_Scanner_triggered()
{
    qDebug()<<"scanner";
    network_scanner * scanner = new network_scanner();
    scanner->show();
}


void MainWindow::on_actionEditor_triggered()
{
    qDebug()<<"Editor";
    Editor * editor = new Editor("");
    editor->show();

}



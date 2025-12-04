#include "system_designer.h"
#include "ui_system_designer.h"
#include <QDebug>
#include "graphicsnodeitem.h"

system_designer::system_designer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::system_designer)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,8);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(1,4);
    this->setWindowTitle("System Designer");
    scene_ = new GraphicsNodeScene(this);

    ui->graphicsView->setScene(scene_);


    //创建 designer 的menu
    ui->toolButton->setText("选项");
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    // 创建关联菜单
    QMenu *optionsMenu = new QMenu(this);

    // 添加菜单项
    QAction *prefsAction = optionsMenu->addAction("首选项...");
    QAction *helpAction = optionsMenu->addAction("帮助");
    optionsMenu->addSeparator();
    QAction *aboutAction = optionsMenu->addAction("关于");
    ui->toolButton->setMenu(optionsMenu);



}

system_designer::~system_designer()
{
    delete ui;
}

void system_designer::on_toolButton_2_clicked()
{
    // // 添加一个节点
    // QGraphicsEllipseItem * node = new QGraphicsEllipseItem(100,200,100,60);

    GraphicsNodeItem * node = new GraphicsNodeItem(0,0,100,60);
    scene_->addItem(node);


}


void system_designer::on_pushButton_clicked()
{
    qDebug()<<"调试信息:";
    for(auto & item : this->scene_->items()){
        qDebug()<<"已经存在ITEM:"<<item->data(0);
    }
}


#ifndef SYSTEM_DESIGNER_H
#define SYSTEM_DESIGNER_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "graphicsnodescene.h"
namespace Ui {
class system_designer;
}

class system_designer : public QMainWindow
{
    Q_OBJECT

public:
    explicit system_designer(QWidget *parent = nullptr);
    ~system_designer();

private slots:
    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::system_designer *ui;
    GraphicsNodeScene * scene_;
};

#endif // SYSTEM_DESIGNER_H

#include "graphicsnodeitem.h"
#include <QPen>
#include <QDebug>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>
#include <QColorDialog>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QObject>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QRectF>
GraphicsNodeItem::GraphicsNodeItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
:QGraphicsEllipseItem(x,y,w,h,parent){
    // 设置初始样式
    // setPen(QPen(Qt::black, 2));
    setBrush(Qt::lightGray);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsPanel);
    setAcceptHoverEvents(true);

    text_item = new QGraphicsTextItem("node");
    text_item->setParentItem(this);
    QRectF item_rect = this->rect();
    QRectF text_item_rect = text_item->boundingRect();
    qreal X = (item_rect.width() - text_item_rect.width()) / 2.0 + item_rect.x();
    qreal Y = (item_rect.height() - text_item_rect.height()) / 2.0 + item_rect.y();
    qDebug()<<"X:"<<X<<" Y:"<<Y << " TX:"<<this->rect().x()<<" TY:"<<this->rect().y() << " itemX:"<<item_rect.x()<<" itmeY:"<<item_rect.y() <<" text_itemX:"<<text_item_rect.x()<<" text_itemY:"<<text_item_rect.y();
    text_item->setPos(X,Y);
    text_item->setData(0,"node_text");
    this->setData(0,"Node");

}
GraphicsNodeItem::~GraphicsNodeItem(){

}


// 鼠标悬停事件
void GraphicsNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    setBrush(Qt::yellow); // 悬停时变为黄色
    setCursor(Qt::PointingHandCursor); // 显示手型光标
}

void GraphicsNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    // 如果不是选中状态，恢复原始颜色
    if (!isSelected()) {
        setBrush(Qt::lightGray);
    }
    setCursor(Qt::ArrowCursor); // 恢复默认光标
}

// 鼠标按下事件
void GraphicsNodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 左键点击：选中状态切换
        setSelected(!isSelected());
        setBrush(Qt::green); // 选中时变为绿色
        qDebug()<<"Item Left Clicked";
        if(nullptr == ite){

        ite = new QGraphicsLineItem(event->scenePos().x(),event->scenePos().y(),50,80);
        ite->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsPanel);
        scene()->addItem(ite);
        }else {
            ite->setPos(event->scenePos().x(),event->scenePos().y());
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        // 右键点击：弹出上下文菜单
        qDebug() << "Item Right-clicked on ellipse at position:"
                 << event->scenePos();
    }

    // 允许拖拽操作
    QGraphicsEllipseItem::mousePressEvent(event);
}

// 鼠标释放事件
void GraphicsNodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);

    // 如果不是悬停状态，恢复颜色
    if (!isSelected() && !isUnderMouse()) {
        setBrush(Qt::lightGray);
    }
}

// 鼠标移动事件
void GraphicsNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 实现拖拽效果
    QGraphicsEllipseItem::mouseMoveEvent(event);
    qDebug() << "Item Ellipse moved to position:" << scenePos();
}

// 位置变化事件
QVariant GraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // 获取新位置
        QPointF newPos = value.toPointF();

        // 可选：限制在场景边界内
        QRectF sceneRect = scene()->sceneRect();
        if (!sceneRect.contains(newPos)) {
            // 保持在场景边界内
            newPos.setX(qMin(sceneRect.right(), qMax(newPos.x(), sceneRect.left())));
            newPos.setY(qMin(sceneRect.bottom(), qMax(newPos.y(), sceneRect.top())));
            return newPos;
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void GraphicsNodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *deleteAction = menu.addAction("Delete");
    QAction *colorAction = menu.addAction("Change Color");
    QAction *lineAction = menu.addAction("Add Line");
    QMenu lineSubMenu;

    auto _items = scene()->items();
    qDebug()<<"Item Node size:"<<_items.size();
    for(auto it:_items){
        QString itemName = it->data(0).toString();
        qDebug()<<"Items:"<<itemName;
        if(it->parentItem() != nullptr){
            qDebug()<<"WHAT:"<<it->parentItem()->data(0);
        }
        if(itemName != this->data(0).toString() && it->parentItem() == nullptr) {
            QAction * node = lineSubMenu.addAction(itemName);
            qDebug()<<">>ADD Action:"<<node->text();
        }
    }



    lineAction->setMenu(&lineSubMenu);

    QAction *selectedAction = menu.exec(event->screenPos());

    if (selectedAction == deleteAction) {
        scene()->removeItem(this);
        delete this;
         qDebug()<<">>>> Delete";
    } else if (selectedAction == colorAction) {
        setBrush(QColorDialog::getColor(brush().color()));
         qDebug()<<">>>> Color";
    }else if(selectedAction == lineAction){
        //DO NOTHING
        ;
    }
    else if(qobject_cast<QMenu*>(selectedAction->parentWidget()) != nullptr && qobject_cast<QMenu*>(selectedAction->parentWidget())->menuAction() == lineAction) {
        qDebug()<<">>>> Line Node:"<<selectedAction->text() ;
        for(auto it:_items){
            QString itemName = it->data(0).toString();
            qDebug()<<"Get Items:"<<itemName;
            if(itemName == selectedAction->text()) {
                // 查找选中的节点并连线
                qreal node1X = this->rect().x() + this->rect().width();
                qreal node1Y = this->rect().y() + this->rect().height() / 2;

                qDebug()<<">>> 添加连线节点:"<<itemName;
                // qDebug()<<"event->pos():"<< event->pos();
                // qDebug()<<"event->scenePos():"<<event->scenePos();
                // qDebug()<<"this->scenePos():"<<this->scenePos();
                // qDebug()<<"this mapToscene():"<<mapToScene(this->pos());
                // qDebug()<<"node mapToscene():"<<mapToScene(dynamic_cast<GraphicsNodeItem*>(it)->rect());

                lineConnect(dynamic_cast<GraphicsNodeItem*>(it));
            }
        }

    }
    // qDebug()<<"Action:"<<selectedAction->text()<< qobject_cast<QMenu*>(selectedAction->parentWidget())->menuAction()->text();
}


static int fuzzyCompareWithOrder(double a, double b, double epsilonScale = 1.0) {
    // 1. 首先检查是否模糊相等
    if (qFuzzyCompare(a, b)) {
        return 0; // 相等
    }
    // 2. 如果不相等，则用差值判断大小
    return (a < b) ? -1 : 1;
}


void GraphicsNodeItem::addLineConnect(const QString &node1_name, qreal node1X,qreal node1Y,const QString & node2_name, qreal node2X,qreal node2Y){
    bool node1_and_node2_is_connected = false;
    for(auto &it : line_ponits_){
        if(it.start_node_name == node1_name && (it.start_point == QPointF(node1X,node1Y))){
            if(it.end_point == QPointF(node2X,node2Y)){
                // 已经连线
                node1_and_node2_is_connected = true;
            }else {
                // node1 已经存在一个连线,但是本次记录没有于node2连线
                node1_and_node2_is_connected = false;
            }
        }
    }
    if(!node1_and_node2_is_connected){
        auto line_item = std::make_shared<QGraphicsLineItem>(node1X,node1Y,node2X,node2Y);
        line_points_t _line_point;
        _line_point.start_node_name = node1_name;
        _line_point.start_point = QPointF(node1X,node1Y);
        _line_point.end_node_name = node2_name;
        _line_point.end_point = QPointF(node2X,node2Y);
        this->line_ponits_.insert(line_item,_line_point);
        scene()->addItem(line_item.get());
    }
}


void GraphicsNodeItem::lineConnect(GraphicsNodeItem * node) {
    qreal node1X = this->scenePos().x() + this->rect().width();
    qreal node1Y = this->scenePos().y() + this->rect().height() / 2;

    // 获取item在scene中的坐标位置
    QPointF this_item = this->scenePos();
    QPointF node_item = node->scenePos();
    // node1 名字
    QString node1_name = this->data(0).toString();
    QString node2_name = node->data(0).toString();
    // qreal node2X = this->scenePos()
    // 中心点位置
    qreal node1_centerX = this_item.x() + this->rect().width() / 2;
    qreal node1_centerY = this_item.y() + this->rect().height() / 2;

    // node1 底部中心
    qreal node1_bottom_centerX = node1_centerX;
    qreal node1_bottom_centerY = node1_centerY + this->rect().height() / 2;
    // node1 右边中心
    qreal node1_right_centerX = node1_centerX +this->rect().width() / 2;
    qreal node1_right_centerY = node1_centerY;

    // node1 上边中心
    qreal node1_top_centerX = node1_centerX;
    qreal node1_top_centerY = node1_centerY - this->rect().height() / 2;

    // node1 左边中心
    qreal node1_left_centerX = node1_centerX - this->rect().width() / 2;
    qreal node1_left_centerY = node1_centerY;


    // node2 中心位置
    qreal node2_centerX = node_item.x() + node->rect().width() / 2;
    qreal node2_centerY = node_item.y() + node->rect().height() / 2;

    // node2 底部中心
    qreal node2_bottom_centerX = node2_centerX;
    qreal node2_bottom_centerY = node2_centerY + node->rect().height() / 2;
    // node2 右边中心
    qreal node2_right_centerX = node2_centerX +node->rect().width() / 2;
    qreal node2_right_centerY = node2_centerY;

    // node2 上边中心
    qreal node2_top_centerX = node2_centerX;
    qreal node2_top_centerY = node2_centerY - node->rect().height() / 2;

    // node2 左边中心
    qreal node2_left_centerX = node2_centerX - node->rect().width() / 2;
    qreal node2_left_centerY = node2_centerY;


    if(node1_centerX < node2_centerX) {
        if(node1_centerY < node2_centerY){
            // 第二象限 下左 下上 右上 右左 取最小距离
            double distance1 = QLineF(QPointF(node1_bottom_centerX,node1_bottom_centerY),QPointF(node2_left_centerX,node2_left_centerY)).length();
            double distance2 = QLineF(QPointF(node1_bottom_centerX,node1_bottom_centerY),QPointF(node2_top_centerX,node2_top_centerY)).length();
            double distance3 = QLineF(QPointF(node1_right_centerX,node1_right_centerY),QPointF(node2_top_centerX,node2_top_centerY)).length();
            double distance4 = QLineF(QPointF(node1_right_centerX,node1_right_centerY),QPointF(node2_left_centerX,node2_left_centerY)).length();
            qDebug()<<"第二象限四个距离:1:"<<distance1<<" 2:"<<distance2<<" 3:"<<distance3<<" 4:"<<distance4;
            if(fuzzyCompareWithOrder(distance1,distance2) < 0){
                if(fuzzyCompareWithOrder(distance3,distance4) < 0) {
                    if(fuzzyCompareWithOrder(distance1,distance3 < 0)){
                        // 1 最小
                        qDebug()<<"1 1最小";
                        addLineConnect(node1_name, node1_bottom_centerX,node1_bottom_centerY,node2_name,node2_left_centerX,node2_left_centerY);

                    }else {
                        // 3 最小
                        qDebug()<<"2 3最小";
                        QGraphicsLineItem  * line_item = new QGraphicsLineItem(node1_bottom_centerX,node1_bottom_centerY,node2_left_centerX,node2_left_centerY);
                        scene()->addItem(line_item);
                    }
                }else {
                    if(fuzzyCompareWithOrder(distance1,distance4)<0){
                        // 1 最小
                        qDebug()<<"3 1最小";
                    }else {
                        // 4 最小
                        qDebug()<<"4 1最小";
                    }
                }
            }else {
                if(fuzzyCompareWithOrder(distance3,distance4)<0) {
                    if(fuzzyCompareWithOrder(distance2,distance3)<0) {
                        // 2 最小
                        qDebug()<<"5 2最小";
                    }else {
                        // 3 最小
                        qDebug()<<"6 3最小";
                    }
                }else {
                    if(fuzzyCompareWithOrder(distance2,distance4)<0) {
                        // 2 最小
                        qDebug()<<"7 2最小";
                    }else {
                        // 4 最小
                        qDebug()<<"8 4最小";
                    }
                }
            }


        }else {
            // 第三象限
        }
    }else {
        if(node1_centerY < node2_centerY){
            // 第一象限
        }else {
            // 第四象限
        }
    }
}


void GraphicsNodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // 创建编辑框
    QLineEdit *edit = new QLineEdit;
    edit->setText("Ellipse Name");

    // // 添加到场景
    QGraphicsProxyWidget *proxy = scene()->addWidget(edit);
    proxy->setPos(event->scenePos());

    // 连接编辑完成信号
    QObject::connect(edit, &QLineEdit::editingFinished, [=]() {
        qDebug() << "New name:" << edit->text();
        text_item->setPlainText(edit->text());
        text_item->setData(0,edit->text());
        this->setData(0,edit->text());
         scene()->removeItem(proxy);
        // delete edit;  // 崩溃
    });

}

#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsEllipseItem>
#include <QList>
#include <QMap>


typedef struct LinePoints{
    QPointF start_point;
    QString start_node_name;
    QPointF end_point;
    QString end_node_name;
}line_points_t;


class GraphicsNodeItem : public QGraphicsEllipseItem
{

public:
    GraphicsNodeItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ~GraphicsNodeItem();

private:
    void addLineConnect(const QString &node1_name,qreal node1X,qreal node1Y,const QString &node2_name,qreal node2X,qreal node2Y);

protected:
    void lineConnect(GraphicsNodeItem * node);

protected:
    // 鼠标悬停事件
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    // 鼠标按下事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // 鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // 鼠标移动事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    // 位置变化事件
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    private:
    QGraphicsTextItem * text_item;
    QGraphicsLineItem * ite{nullptr};
    QMap<std::shared_ptr<QGraphicsLineItem>,line_points_t> line_ponits_;


};

#endif // GRAPHICSNODEITEM_H

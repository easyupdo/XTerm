#ifndef GRAPHICSNODESCENE_H
#define GRAPHICSNODESCENE_H

#include <QGraphicsScene>
#include <QObject>

class GraphicsNodeScene : public QGraphicsScene
{
public:
    explicit GraphicsNodeScene(QObject *parent = nullptr);
    ~GraphicsNodeScene();

    // 鼠标按下事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // 鼠标移动事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override ;

    // 鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // 鼠标双击事件
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void handleLeftClick(QGraphicsSceneMouseEvent *event);

    void handleRightClick(QGraphicsSceneMouseEvent *event);

    void startRubberBandSelection(const QPointF &pos);

    void showContextMenu(const QPoint &screenPos);

    QPointF m_lastMousePos;
    QPointF m_rubberBandOrigin;
    QGraphicsRectItem *m_rubberBand = nullptr;
};

#endif // GRAPHICSNODESCENE_H

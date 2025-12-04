#include "graphicsnodescene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QMenu>

GraphicsNodeScene::GraphicsNodeScene(QObject *parent)
    : QGraphicsScene{parent}
{}


GraphicsNodeScene::~GraphicsNodeScene() {

}

// 鼠标按下事件
void GraphicsNodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Scene Mouse pressed at scene position:" << event->scenePos();

    if (event->button() == Qt::LeftButton) {
        // 左键点击处理
        handleLeftClick(event);
    } else if (event->button() == Qt::RightButton) {
        // 右键点击处理
        handleRightClick(event);
    }

    QGraphicsScene::mousePressEvent(event); // 传递给子项
}

// 鼠标移动事件
void GraphicsNodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // 实时更新鼠标位置
    m_lastMousePos = event->scenePos();

    // 更新状态提示
    // emit mousePositionChanged(m_lastMousePos);

    QGraphicsScene::mouseMoveEvent(event);
}

// 鼠标释放事件
void GraphicsNodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Scene Mouse released at:" << event->scenePos();
    QGraphicsScene::mouseReleaseEvent(event);
}

// 鼠标双击事件
void GraphicsNodeScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // createItemAtPosition(event->scenePos());
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}


void GraphicsNodeScene::handleLeftClick(QGraphicsSceneMouseEvent *event) {
    // 检查是否点击了空白区域
    if (!itemAt(event->scenePos(), QTransform())) {
        startRubberBandSelection(event->scenePos());
    }
}

void GraphicsNodeScene::handleRightClick(QGraphicsSceneMouseEvent *event) {
    // 显示场景上下文菜单
    showContextMenu(event->screenPos());
}

void GraphicsNodeScene::startRubberBandSelection(const QPointF &pos) {
    // 实现橡皮筋选择
    m_rubberBandOrigin = pos;
    if (!m_rubberBand) {
        m_rubberBand = new QGraphicsRectItem;
        m_rubberBand->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        m_rubberBand->setBrush(QBrush(QColor(100, 100, 255, 50)));
        addItem(m_rubberBand);
    }
}

void GraphicsNodeScene::showContextMenu(const QPoint &screenPos) {
    QMenu menu;

}

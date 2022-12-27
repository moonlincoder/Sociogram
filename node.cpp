#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QPainter>
#include <QApplication>
#include <QtMath>

Node::Node(GraphWidget *pGraph)
    : mp_graph(pGraph)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *pEdge)
{
    mp_edges << pEdge;
    pEdge->adjust();
}

bool Node::advancePosition()
{
  return !(m_newPos == pos());
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change) {
    case ItemPositionChange: {
        QPointF newPos = value.toPointF();
        foreach(Edge *edge, mp_edges) {
            edge->adjust();
        }

        if(QApplication::mouseButtons() == Qt::LeftButton) {
            int gridSize = mp_graph->gridSize();
            qreal xV = round(newPos.x() / gridSize) * gridSize;
            qreal yV = round(newPos.y() / gridSize) * gridSize;
            return QPointF(xV, yV);
        }
        mp_graph->itemMoved();
        break;
    }
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

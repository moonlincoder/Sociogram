#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QPainterPath>

class GraphWidget;
class Edge;
class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *);

    void addEdge(Edge *);
    QList<Edge *> getEdges() const { return mp_edges; }

    bool advancePosition();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> mp_edges;
    QPointF m_newPos;
    GraphWidget* mp_graph;
};

#endif // NODE_H

#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include <QGraphicsItem>

class Node;
class Edge : public QGraphicsItem
{
public:
    Edge(Node *pSourceNode, Node *pDestNode);

    Node *sourceNode() const {
        return mp_source;
    }

    Node *destNode() const {
        return mp_dest;
    }

    void adjust();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    Node *mp_source = Q_NULLPTR;
    Node *mp_dest = Q_NULLPTR;

    QPointF m_sourcePoint;
    QPointF m_destPoint;
    qreal m_arrowSize;
};

#endif // EDGE_H

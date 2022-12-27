
#include "graphwidget.h"
#include "node.h"
#include "edge.h"

#include <QKeyEvent>
#include <QWheelEvent>

GraphWidget::GraphWidget(QWidget *parent, int gridSize)
  : QGraphicsView(parent), m_timerId(0), m_gridSize(gridSize), m_gridPenSize(2) {
  mp_scene = new QGraphicsScene(this);
  mp_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  mp_scene->setSceneRect(-200, -200, 400, 400);
  setScene(mp_scene);

  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
  setMinimumSize(400, 400);

  Node *node1 = new Node(this);
  Node *node2 = new Node(this);

  mp_scene->addItem(node1);
  mp_scene->addItem(node2);
  mp_scene->addItem(new Edge(node1, node2));

  node2->setPos(convertToGridPoint(0), convertToGridPoint(-150));

}
int GraphWidget::addNode(std::vector<int> nodes) {
    Node *NewNode = new Node(this);
    mp_scene->addItem(NewNode);

    for(auto node : nodes){
        mp_scene->addItem(new Edge(NewNode, (Node *) mp_scene->items()[node]));
    }
    int x = (mp_scene->items().count() % 6) * mp_scene->width() / 6, y = (mp_scene->items().count() / 6) *
            mp_scene->height() / 6;

    NewNode->setPos(convertToGridPoint(x), convertToGridPoint(y));
    return mp_scene->items().count();
}
int GraphWidget::removeNode(int index){
    mp_scene->removeItem(mp_scene->items()[index]);
    return 1;
}
void GraphWidget::itemMoved()
{
  if(!m_timerId) {
    m_timerId = startTimer(100 / 25);
  }
}

void GraphWidget::setGridSize(int gridSize)
{
  m_gridSize = gridSize;
}

void GraphWidget::setGridPenSize(int gridPenSize)
{
  m_gridPenSize = gridPenSize;
}

void GraphWidget::zoomIn()
{

}

void GraphWidget::zoomOut()
{

}

void GraphWidget::keyPressEvent(QKeyEvent *pEvent)
{
  switch(pEvent->key()) {
    case Qt::Key_Plus:
      zoomIn();
      break;
    case Qt::Key_Minus:
      zoomOut();
      break;
    default:
      QGraphicsView::keyPressEvent(pEvent);
      break;
  }
}

void GraphWidget::timerEvent(QTimerEvent *)
{
  QList<Node *> nodes;
  foreach(QGraphicsItem *pItem, mp_scene->items()) {
    if(Node *pNode = qgraphicsitem_cast<Node *>(pItem)) {
      nodes << pNode;
    }
  }

  bool itemsMoved = false;
  foreach(Node *pNode, nodes) {
    if(pNode->advancePosition()) {
      itemsMoved = true;
    }
  }

  if(!itemsMoved) {
    killTimer(m_timerId);
    m_timerId = 0;
  }
}

void GraphWidget::wheelEvent(QWheelEvent *event) {
  scaleView(std::pow(static_cast<double>(2), -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF & rect)
{
  QPen pen;
  pen.setWidth(m_gridPenSize);
  pen.setCosmetic(true);
  pen.setColor(Qt::black);
  painter->setPen(pen);

  // x-coordinate
  qreal left = int(rect.left()) - (int(rect.left()) % m_gridSize);

  // y-coordinate
  qreal top = int(rect.top()) - (int(rect.top()) % m_gridSize);

  QVector<QPointF> points;
  for(qreal x = left; x < rect.right(); x += m_gridSize) {
    for(qreal y = top; y < rect.bottom(); y += m_gridSize) {
      points.append(QPointF(x, y));
    }
  }

  painter->drawPoints(points);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
      return;

  scale(scaleFactor, scaleFactor);
}

int GraphWidget::convertToGridPoint(int pos) const
{
    return pos - pos % m_gridSize;
}

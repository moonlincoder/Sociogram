#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>

#include <cmath>

#include <QList>
#include <QVector>
#include <QDebug>

class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = Q_NULLPTR, int gridSize = 1);

    void itemMoved();

    int gridSize() const { return m_gridSize; }
    void setGridSize(int gridSize);
    int gridPenSize() const { return m_gridPenSize; }
    void setGridPenSize(int gridPenSize);
    int addNode(std::vector<int> nodes);
    int removeNode(int index);
    QGraphicsScene* getScene() const { return mp_scene; }

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *pEvent) override;
    void timerEvent(QTimerEvent *) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);

private:
    int m_timerId;
    QGraphicsScene *mp_scene;
    Node *mp_centerNode;

    int m_gridSize;
    int m_gridPenSize;

    int convertToGridPoint(int pos) const;
};

#endif // GRAPHWIDGET_H

#ifndef pGraphicsScene_H
#define pGraphicsScene_H

#include <QGraphicsScene>
#include <QGraphicsItem>


class pGraphicsScene : public QGraphicsScene
{
     Q_OBJECT
public:
    pGraphicsScene();

    void SetCycleRadius(int radius_);
    void LoadImages(QString image_);
    void ShowCycle(bool show_);
    QPointF GetCyclePos();
protected:
     void drawBackground(QPainter *painter, const QRectF &rect);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
//     QGraphicsRectItem *m_printTableItem;
//     QGraphicsRectItem* m_rectItem;

     QGraphicsEllipseItem* m_cycleItem;
     QGraphicsPixmapItem* m_pixmapItem;


     qreal pDpm;
};

#endif // pGraphicsScene_H

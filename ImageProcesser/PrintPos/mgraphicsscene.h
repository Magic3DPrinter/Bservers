#ifndef MGRAPHICSSCENE_H
#define MGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include "MyItem.h"
#include "mpixmapitem.h"

class mGraphicsScene : public QGraphicsScene
{
     Q_OBJECT
public:
    mGraphicsScene();
    void resetTable(int w,int h);
    QPointF getPixmapPos();
    qreal getDPM();
    void setPixmapPos(QPointF m);
    void redrawPic(QString path);
    void loadImage(QString pp);
protected:
     void drawBackground(QPainter *painter, const QRectF &rect);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
     QGraphicsRectItem *m_printTableItem;
     QGraphicsRectItem* m_rectItem;
     QGraphicsEllipseItem* m_cycleItem;

     mPixmapItem *m_picItem;
     qreal pDpm;
};

#endif // MGRAPHICSSCENE_H

#ifndef MPIXMAPITEM_H
#define MPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class mPixmapItem : public QGraphicsPixmapItem
{
//    Q_OBJECT
public:
    explicit mPixmapItem();
    QRectF boundingRect()const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
    void ResetRect(QRectF rect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QRectF m_rect;
    bool cScale;
    QCursor* m_cursor;
    QPointF start;
    QPointF end;
    int direction;
};

#endif // MPIXMAPITEM_H

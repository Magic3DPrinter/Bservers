#include "pGraphicsScene.h"
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>

pGraphicsScene::pGraphicsScene()
{
    m_cycleItem = new QGraphicsEllipseItem();
    m_pixmapItem = new QGraphicsPixmapItem();

    m_cycleItem->setRect(0,0,200,200);
    QPen pens(Qt::red);

    this->addItem(m_pixmapItem);
//    pens.setStyle(Qt::DotLine);
    m_cycleItem->setPen(pens);
    m_cycleItem->setFlag(QGraphicsItem::ItemIsMovable);
    this->addItem(m_cycleItem);
    m_cycleItem->hide();
}
void pGraphicsScene::ShowCycle(bool show_)
{
    if(show_)
    {
       m_cycleItem->show();
    }
    else
    {
         m_cycleItem->hide();

    }
}
void pGraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2) {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }
//    m_backgroundColor(16, 90, 145);
    glClearColor(16, 90, 145, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void pGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<tr("当前点坐标X=%1,Y=%2").arg(event->scenePos().x()).arg(event->scenePos().y());
    QGraphicsScene::mousePressEvent(event);
}

void pGraphicsScene::LoadImages(QString image_)
{
    m_pixmapItem->setPixmap(QPixmap(image_));
}

QPointF pGraphicsScene::GetCyclePos()
{
    return m_cycleItem->scenePos();
}
void pGraphicsScene::SetCycleRadius(int radius_)
{
    m_cycleItem->setRect(0,0,radius_,radius_);
}

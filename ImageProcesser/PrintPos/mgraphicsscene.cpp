#include "mgraphicsscene.h"
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>

mGraphicsScene::mGraphicsScene()
{

    m_printTableItem = new QGraphicsRectItem();
    m_picItem = new mPixmapItem();

    //测试分辨率
    QScreen* desktopWidget = QApplication::screens().at(0);
    qreal pdpi = desktopWidget->logicalDotsPerInch();
    qreal pphyDot = desktopWidget->physicalDotsPerInch();
    pDpm = (1.087*pphyDot)/25.4;
    qDebug()<<QObject::tr("framGeo:%1").arg(pphyDot);

    QPen pent(Qt::blue);
    m_rectItem = new QGraphicsRectItem(0, 0, (100*pDpm), (100*pDpm));
    m_rectItem->setPen(pent);
    addItem(m_rectItem);
    QGraphicsTextItem * pans = new QGraphicsTextItem();
    pans->setHtml("<font color=\"red\">蓝色为打印机可打印区域，红色为底材料区域</font> ");
    pans->setPos(100*pDpm+5,5);
    addItem(pans);

    QPen pens(Qt::red);
    pens.setStyle(Qt::DotLine);
    m_printTableItem = new QGraphicsRectItem(0, 0, (90*pDpm), (90*pDpm));
    m_printTableItem->setPen(pens);
    m_printTableItem->setPos(0,0);
//    m_printTableItem->setFlag(QGraphicsItem::ItemIsMovable);
    addItem(m_printTableItem);
}

void mGraphicsScene::redrawPic(QString path)
{
    QPixmap free(path);
    QBitmap mask= free.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor);    //创建白色像素的掩码 位图
    free.setMask(mask);
    m_picItem->ResetRect(QRectF(0,0,free.width(),free.height()));
    m_picItem->setPixmap(free);

}
void mGraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2) {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }
//    m_backgroundColor(16, 90, 145);
    glClearColor(16, 90, 145, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void mGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<tr("当前点坐标X=%1,Y=%2").arg(event->scenePos().x()).arg(event->scenePos().y());
    QGraphicsScene::mousePressEvent(event);
}
void mGraphicsScene::resetTable(int w,int h)
{
    m_printTableItem->setRect(QRectF(0,0,w*pDpm,h*pDpm));
}

QPointF mGraphicsScene::getPixmapPos()
{
    QPointF f(m_picItem->pixmap().width()/(2*pDpm),m_picItem->pixmap().height()/(2*pDpm));
    return (f+(m_picItem->scenePos()/pDpm));
}
qreal mGraphicsScene::getDPM()
{
    return pDpm;
}
void mGraphicsScene::setPixmapPos(QPointF m)
{
     QPointF f(m_picItem->pixmap().width()/(2*pDpm),m_picItem->pixmap().height()/(2*pDpm));
     qDebug()<<QObject::tr("set X=%1,Y=%2").arg(m.x()).arg(m.y());
     m_picItem->setPos(m-f);
}
void mGraphicsScene::loadImage(QString pp)
{
    QImage temp(pp);
    temp.save("temp1.png","PNG",100);
    QImage saved;
    if(temp.width()>temp.height())
    {
        int h1 = (80*pDpm/(temp.width()*1.0))*temp.height();
        saved = temp.scaled(80*pDpm,h1,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    }
    else
    {
        int w1 = (80*pDpm/(temp.height()*1.0))*temp.width();
        saved = temp.scaled(w1,80*pDpm,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    }
    saved.save("first.png","PNG",100);
    QPixmap free("first.png");
    QBitmap mask= free.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor);    //创建白色像素的掩码 位图
    free.setMask(mask);

    if(m_picItem->pixmap().isNull())
    {
        m_picItem->ResetRect(QRectF(0,0,free.width(),free.height()));
        m_picItem->setPixmap(free);
        addItem(m_picItem);
        m_picItem->setPos(5,5);
    }
    else
    {
        m_picItem->ResetRect(QRectF(0,0,free.width(),free.height()));
        m_picItem->setPixmap(free);
        m_picItem->setPos(5,5);
    }
}

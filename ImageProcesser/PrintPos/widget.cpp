#include "widget.h"
#include "ui_widget.h"
#include "mgraphicsscene.h"
#include <QGLWidget>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    pScene = new mGraphicsScene();
    ui->setupUi(this);
    this->setWindowTitle(tr("编辑模板"));
    view = new QGraphicsView();
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setScene(pScene);
//    ui->graphicsView->resize(400,200);

    QScreen* desktopWidget = QApplication::screens().at(0);
    qreal pdpi = desktopWidget->logicalDotsPerInch();
    qreal pphyDot = desktopWidget->physicalDotsPerInch();

//    qDebug()<<QObject::tr("framGeo:%1").arg(pphyDot);
    ui->debugLabel->setText(tr("logic dpi =%1,physi dpi=%2 ").arg(pdpi).arg(pphyDot));
    updateCombox();


}
void Widget::updateCombox()
{
    QDir *dir=new QDir("./mb");
    QStringList filter;
    ui->MBcomboBox->clear();
    filter<<"*.mb";
    dir->setNameFilters(filter);
    QList<QFileInfo> * fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    ui->MBcomboBox->addItem(" ");
    for(int i=0;i<fileInfo->size();i++)
    {
        ui->MBcomboBox->addItem(fileInfo->at(i).fileName());
    }
    ui->MBcomboBox->setCurrentIndex(0);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_certen_clicked()
{
    pScene->resetTable(ui->tableX->text().toInt(),ui->tableY->text().toInt());
}

//void Widget::on_debug_clicked() //功能测试键
//{
//    QPointF re = pScene->getPixmapPos();
//    qDebug()<<tr("图片中心偏移坐标:X=%1,Y=%2").arg(re.x()).arg(re.y());
//}

void Widget::on_comboBox_activated(const QString &arg1)     //图片打印尺寸变化
{
    QImage temp("temp1.png");
    QImage saved;
    float scale = 1.0;
    qreal dpm = pScene->getDPM();
    if(temp.width()>temp.height())
    {
        scale = arg1.toInt()*dpm/(temp.width()*1.0);
        int h1 = scale*temp.height();
        saved = temp.scaled(arg1.toInt()*dpm,h1,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    }
    else
    {
        scale = arg1.toInt()*dpm/(temp.height()*1.0);
        int w1 = scale*temp.width();
        saved = temp.scaled(w1,arg1.toInt()*dpm,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    }
    saved.save("temp1.png","PNG",100);
    pScene->redrawPic("temp1.png");
}

void Widget::loadFile(QString p)
{
    pScene->loadImage(p);
    ui->comboBox->setCurrentText("90");
}
//void Widget::on_load_clicked()
//{
//    QString picName = QFileDialog::getOpenFileName(this, tr("Open File"),"./",tr("Images (*.png *.jpeg *.jpg)"));
//    pScene->loadImage(picName);
//    ui->comboBox->setCurrentText("80");
//}
QString Widget::getPicSize()
{
    return ui->comboBox->currentText();
}
QPointF Widget::getPicPos()
{
    return pScene->getPixmapPos();
}

//保存模板按键按下触发的槽函数
void Widget::on_saveModel_clicked()
{
    if(ui->modelName->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("请输入模板的名称再保存"));
    }
    else
    {
        QFile file("./mb/"+ui->modelName->text()+".mb");
        file.open(QIODevice::ReadWrite);
        QTextStream writeStream(&file);
        QString tX = ui->tableX->text();    //底料长
        QString tY = ui->tableY->text();    //底料宽
        QString imgSize = ui->comboBox->currentText();
        QString pX = QString::number(((int)pScene->getPixmapPos().x()));  //图片中心位置 x
        QString pY = QString::number(((int)pScene->getPixmapPos().y()));  //图片中心位置 y
        writeStream<<imgSize<<"\n";
        writeStream<<tX<<"\n";
        writeStream<<tY<<"\n";
        writeStream<<pX<<"\n";
        writeStream<<pY<<"\n";
        file.close();
        emit Sig_updateMB();
        updateCombox();
        QMessageBox::information(this,tr("提示"),tr("模板保存完毕"));
    }
}

void Widget::on_MBcomboBox_activated(const QString &arg1)
{
    if(arg1!=" ")
    {
        ui->modelName->setText(arg1);
        QFile file("./mb/"+arg1);
        file.open(QIODevice::ReadWrite);
        QTextStream writeStream(&file);
        QString imgSize = writeStream.readLine();
        QString tX = writeStream.readLine();  //底料 x
        QString tY = writeStream.readLine();  //底料 y
        QString pX = writeStream.readLine();  //图片中心位置 x
        QString pY = writeStream.readLine();  //图片中心位置 y
        ui->tableX->setText(tX);
        ui->tableY->setText(tY);
        pScene->resetTable(ui->tableX->text().toInt(),ui->tableY->text().toInt());
        QPointF m(pX.toInt(),pY.toInt());
        pScene->setPixmapPos(m);
        ui->comboBox->setCurrentText(imgSize);  //设置大小
        on_comboBox_activated(imgSize);
        file.close();
    }
    else
    {

    }
}

void Widget::on_deleteMB_clicked()
{
    if(ui->MBcomboBox->currentText()!=" ")
    {
        QString files = "./mb/"+ui->MBcomboBox->currentText();
        QFile::remove(files);
        updateCombox();
    }
}

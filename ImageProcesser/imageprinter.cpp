#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QGLWidget>
#include <QProcess>

#include "imageprinter.h"
#include "ui_imageprinter.h"

ImagePrinter::ImagePrinter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImagePrinter)
{
    ui->setupUi(this);
    printPos = new Widget();
    pScene = new pGraphicsScene();
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setScene(pScene);

    //添加文字的对话框
    font_dialog = new FontDialog();
    connect(font_dialog,SIGNAL(Sig_addText()),this,SLOT(addText()));
    connect(printPos,SIGNAL(Sig_updateMB()),this,SLOT(slotUpdateMB()));

    //模板定位，定位打印机的位置
    pixSize = "90";
    show_cycle_ = false;
    printCenter = QPoint(50000,50000);
    slotUpdateMB();
}

ImagePrinter::~ImagePrinter()
{
    delete ui;
}

//图片编辑开始//////////////////////////////////////

void ImagePrinter::on_addText_clicked()       //添加文字
{
  font_dialog->show();
}
void ImagePrinter::addText()
{
//    qDebug()<<"now in the add text slot";
//    QImage  tcurrentImg = handleImage(grayscale,scale);
//    QPainter painter(&tcurrentImg); //为这个QImage构造一个QPainter
//    QPen pen = painter.pen();
//    pen.setColor(Qt::black);

//    QFont font = font_dialog->getFont();
//    QPoint po = font_dialog->getPos();
//    QString text = font_dialog->getText();
//    font.setBold(true);//加粗

//    painter.setPen(pen);
//    painter.setFont(font);
//    painter.drawText(tcurrentImg.rect(),Qt::AlignLeft,tr("%1").arg(text));
//    tcurrentImg.save("temp.png","PNG",100);
//    currentImg = tcurrentImg;
}

cv::Mat ImagePrinter::QImageToCvMat( const QImage &inImage, bool inCloneImageData)        //Qimage to Mat
{
  switch (inImage.format())
  {
     // 8-bit, 4 channel
     case QImage::Format_RGB32:
     {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );
        return (inCloneImageData ? mat.clone() : mat);
     }

     // 8-bit, 3 channel
     case QImage::Format_RGB888:
     {
        if ( !inCloneImageData )
           qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

        QImage   swapped = inImage.rgbSwapped();
        return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
     }
     // 8-bit, 1 channel
     case QImage::Format_Indexed8:
     {
        cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());
        return (inCloneImageData ? mat.clone() : mat);
     }
     default:
        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
  }

  return cv::Mat();
}
QImage ImagePrinter::cvMatToQImage( const cv::Mat &inMat )
  {
     switch ( inMat.type() )
     {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
           return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
           return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
           static QVector<QRgb>  sColorTable;

           // only create our color table once
           if ( sColorTable.isEmpty() )
           {
              for ( int i = 0; i < 256; ++i )
                 sColorTable.push_back( qRgb( i, i, i ) );
           }

           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

           image.setColorTable( sColorTable );

           return image;
        }

        default:
           qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
           break;
     }

     return QImage();
  }

void ImagePrinter::ScalePicture(float scale)    //缩放图片尺寸
{
    QImage pos_1 = QImage(*grayImg);
    QImage pos;
    if(QFile("temp1.png").exists())
    {
        QFile::remove("temp1.png");
    }
    pos = pos_1.scaled(scale*(pos_1.width()),scale*(pos_1.height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->p_width->setText(tr("%1").arg(pos.width()));
    ui->p_height->setText(tr("%1").arg(pos.height()));
    currentImg = pos;
    ui->pixValue->setText(tr("图片大小:%1x%2").arg(pos.width()).arg(pos.height()));
//    pos.save("temp.png","PNG",100);
    pos.save("temp.png","PNG",100);
    pScene->LoadImages("temp.png");
}

void ImagePrinter::GrayScalePicture(int grayscale)
{

    QImage tempImg;  //用于缩放
    if(QFile("temp1.png").exists())
    {
        tempImg = QImage("temp1.png");
    }
    else
    {
        tempImg = QImage("temp.png");
    }
    QImage pos_1 = tempImg;                         //拷贝

    QImage pos;
    if(free->format()>3)
    {
        QRgb *pixels = (QRgb *)tempImg.scanLine(0);
        QRgb *grays = (QRgb *)pos_1.scanLine(0);
        QRgb thread = qRgb(grayscale,grayscale,grayscale);
        QRgb threadw = qRgb(255,255,255);
        QRgb threadb = qRgb(0,0,0);
        for(int y =0;y<tempImg.height();y++)
        {
            for(int x=0;x<tempImg.width();x++)
            {
                if(pixels[x+y*(tempImg.width())]>thread)
                   grays[x+y*(tempImg.width())] = threadw;
                else
                    grays[x+y*(tempImg.width())] = threadb;
            }
        }
        currentImg = pos_1;
    }
    else
    {
        currentImg = pos_1;
    }
    ui->pixValue->setText(tr("图片大小:%1x%2").arg(pos.width()).arg(pos.height()));
    pos_1.save("temp.png","PNG",100);       //变换了灰度值的图
    pScene->LoadImages("temp.png");
}

void ImagePrinter::on_openPix_clicked()       //装载图片
{
    openFile = QFileDialog::getOpenFileName(this,tr("选择打印文件"),".",tr("模型文件( *.png *.jpeg *.jpg)"));
    free = new QImage(openFile);
    if(!openFile.isNull())
    {
        ui->BinarySlider->setEnabled(true);
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("未选中任何图片！"));
        return ;
    }
    Mat src1 = imread(openFile.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
    Mat target_ad;

    cv::adaptiveThreshold(src1, target_ad, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 13, 8);
//    cv::threshold(src1, target_otsu, 125, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    cv::imwrite("adaptiveThreshold.jpg",target_ad);
    QImage po("adaptiveThreshold.jpg");
//    po = po.mirrored(true,false);

    po.save("adaptiveThreshold.jpg");
    qDebug()<<tr("w = %1,h = %2").arg(free->width()).arg(free->height());
    if(free->height()>this->height()||free->width()>this->height())
    {
        float scales_h = 1;
        float scales_w = 1;
        float scales = 1;
        scales_h = (this->height()*1.0)/free->height();
        scales_w = (this->width()*1.0)/free->width();
        scales = 0.5*qMin(scales_h,scales_w);
        qDebug()<<QObject::tr("缩放大小：%1").arg(scales);
        grayImg = new QImage(free->scaled(scales*(free->width()),scales*(free->height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        imgfileLoaded = true;
    }
    else
    {
        grayImg = new QImage(*free);
        imgfileLoaded = true;
    }

    grayImg->save("temp.png","PNG",100);
    currentImg = *grayImg;
    ui->p_width->setText(tr("%1").arg(currentImg.width()));
    ui->p_height->setText(tr("%1").arg(currentImg.height()));

    currentImg.save("temp.png","PNG",100);
    pScene->LoadImages("temp.png");

}

void ImagePrinter::on_printPix_clicked()      //打印图片
{
    if(imgfileLoaded)
    {
        savePrintFile("temp.gcode");
        //发送打印的指令
        printableList.append("temp.gcode");
//        emit Sig_print();
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("未装载任何图片！"));
    }

}

void ImagePrinter::on_savePix_clicked()       //保存切好的g-code
{
    if(imgfileLoaded)
    {
        QString fileName;
        fileName = QFileDialog::getSaveFileName(this,tr("保存Gcode文件"), "", tr("Config Files (*.gcode)"));
        QDir sliceFile = QDir("./temp.gcode");
        if(sliceFile.exists())
        {
            QFile::copy("./temp.gcode", fileName);
            qDebug()<<"image generate to stl finish";
        }
        else
        {
            qDebug()<<"generate stl error";
            savePrintFile(fileName);
        }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("未装载任何图片！"));
    }
}

void ImagePrinter::savePrintFile(QString direct)
{
    if(imgfileLoaded)
    {
        //1.保存图片
        //2.图片转化为stl
        //3.调用切片软件
        //4.保存g-code
        fffProcessor *processor;
        ConfigSettings config;
        if(ui->mbList->currentText().isEmpty())
        {
            QMessageBox::information(this,tr("提示"),tr("没有选择打印模板！"));
        }
        else
        {
            on_mbList_activated(ui->mbList->currentText());
            config.setPosConfig((int)printCenter.x(),(int)printCenter.y());
            processor = new fffProcessor(config);
            QLabel *message = new QLabel();
            message->setMinimumSize(message->sizeHint());
            message->setAlignment(Qt::AlignHCenter);

            QImage picture_mirrir("temp.png");
            picture_mirrir = picture_mirrir.mirrored(true,false);
            picture_mirrir.save("temp.png","PNG",100);

            Enable_User_Waiting_Cursor();
            QProcess* free;     //调用外部可执行程序或shell命令的类
            QStringList po;     //参数列表
            po.append("temp.png");
            po.append("temp.stl");
            if(filled)
            {
                po.append("invert");
            }
            else
                po.append("noinvert");

            po.append(pixSize);
            if(free->execute("./load/load.exe",po))
            {
                qDebug()<<"load finished!!";
            }
            char*  stl;
            char* gcode;

            QByteArray b_stl = po.at(1).toLatin1();
            stl=b_stl.data();

            QByteArray b_gcode = direct.toLatin1();
            gcode = b_gcode.data();
            processor->setTargetFile(gcode);
            processor->processFile(stl);

            Disable_User_Waiting_Cursor();
            QFile im(direct);

            if(im.open(QFile::WriteOnly|QIODevice::Append))
            {
                QString endCode = "\nG1 Z15 F2500 \n";

                im.write(endCode.toLatin1());

                QMessageBox::information(this,tr("提示"),tr("gcode尾部写入成功"));
                im.close();
            }
            else
            {
                QMessageBox::information(this,tr("警告"),tr("gcode未写入"));
            }

            QMessageBox::information(this,tr("通知"),tr("照片处理完成！"));
            delete processor;
        }
//        Sig_preview("temp.stl");
//        ui->tabWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("未装载任何图片！"));
    }
}
void ImagePrinter::on_BinarySlider_sliderMoved(int position)  //the gray value changed
{
    grayscale = position;
    GrayScalePicture(position);
//    handleImage(grayscale,1);
}

void ImagePrinter::on_BinarySlider_valueChanged(int value)
{
    grayscale = value;
    GrayScalePicture(value);
}
void ImagePrinter::on_p_height_returnPressed()        //输入图片长度
{
    scale = ui->p_height->text().toFloat()/currentImg.height();
    ScalePicture(scale);
//    handleImage(grayscale,scale);
}

void ImagePrinter::on_p_width_returnPressed()         //输入图片高度
{
   scale = ui->p_width->text().toFloat()/currentImg.width();
   ScalePicture(scale);
}

void ImagePrinter::Enable_User_Waiting_Cursor()
{
    QCursor curs;
    curs.setShape(Qt::WaitCursor);
    QApplication::setOverrideCursor(curs);
}

void ImagePrinter::Disable_User_Waiting_Cursor()
{
    QCursor curs;
    curs.setShape(Qt::ArrowCursor);
    QApplication::setOverrideCursor(curs);
}

void ImagePrinter::on_preHeart_clicked()  //pre heat
{

    if(connected)
    {
        emit Sig_preHeart();
    }
    else
    {
        QMessageBox::information(this,tr("警告"),tr("没有链接打印机！"));
        qDebug()<<tr("没有连接打印机！");
    }

}

void ImagePrinter::on_fill_clicked(bool checked)  //fill 填充
{
    QImage pix("adaptiveThreshold.jpg");
    QImage save=pix;
    if(pix.height()>this->height()||pix.height()>this->height())
    {
        float scales_h = 1;
        float scales_w = 1;
        float scales = 1;
        scales_h = (this->height()*1.0)/pix.height();
        scales_w = (this->width()*1.0)/pix.width();
        scales = 0.5*qMin(scales_h,scales_w);
//        if(scales_h>scales_w)

        qDebug()<<QObject::tr("缩放大小：%1").arg(scales);
        save = QImage(pix.scaled(scales*(pix.width()),scales*(pix.height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        save.save("temp.png","PNG",100);
    }
    else
    {
        pix.save("temp.png","PNG",100);
    }
//    ui->PictureLabel->setPixmap(QPixmap::fromImage(save, Qt::AutoColor));

}
void ImagePrinter::on_pushButton_3_clicked()      //与加热
{
    if(connected)
    {
        emit Sig_preHeart();
    }
    else
    {
        QMessageBox::information(this,tr("警告"),tr("没有链接打印机！"));
        qDebug()<<tr("没有连接打印机！");
    }
}

void ImagePrinter::on_lineEdit_returnPressed()        //改变针头的宽度
{
    int temp = ui->lineEdit->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("slice");
    settings->setValue("widthE",QVariant(temp));
    settings->endGroup();
}


void ImagePrinter::slotUpdateMB() //更新MB的列表
{
    QDir *dir=new QDir("./mb");
    QStringList filter;
    filter<<"*.mb";
    dir->setNameFilters(filter);
    fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(int i=0;i<fileInfo->size();i++)
    {
        ui->mbList->addItem(fileInfo->at(i).fileName());
    }
    if(QFile("temp1.png").exists())
    {
        QFile::remove("temp1.png");
    }
}
void ImagePrinter::on_printPosbt_clicked()        //打开定位板
{
    {
        printPos->loadFile("mb.jpg");
        printPos->show();
    }

}
void ImagePrinter::on_mbList_activated(const QString &arg1)       //定位模板选择
{
    QString mb = "./mb/"+arg1;
    QFile file(mb);
    file.open(QIODevice::ReadWrite);
    QTextStream st(&file);
    QString imgPix = st.readLine();
    st.readLine();
    st.readLine();
    QString imgX = st.readLine();
    QString imgY = st.readLine();
    pixSize = imgPix;
    printCenter.setX(imgX.toInt()*1000);
    printCenter.setY(imgY.toInt()*1000);
    file.close();
}



void ImagePrinter::on_radiusLineEdit_editingFinished()      //完成圆半径设置
{
    int current_radius = ui->radiusLineEdit->text().toInt();
    pScene->SetCycleRadius(current_radius);
}
void ImagePrinter::on_useRadius_clicked()               //决定是否显示圆
{
    if(show_cycle_)
    {
        show_cycle_ = false;
        pScene->ShowCycle(show_cycle_);
    }
    else
    {
        show_cycle_ = true;
        pScene->ShowCycle(show_cycle_);
    }
}

void ImagePrinter::on_rebuildPicture_clicked()          //生成对应的圆角
{
    int current_radius = ui->radiusLineEdit->text().toInt()/2-5;
    QPointF center = pScene->GetCyclePos()+QPointF(current_radius,current_radius);
    DrawClcle("temp.png",center,current_radius);
    pScene->LoadImages("temp1.png");
}

void ImagePrinter::DrawClcle(QString picture_path_,QPointF center_,int radius_)   //画一个圆形图
{
    QImage* picture = new QImage(picture_path_);
    QRgb* pixcel_array = (QRgb*)picture->scanLine(0);
    QRgb  black = qRgb(0,0,0);
    QRgb white = qRgb(255,255,255);
    QPoint center = QPoint((int)center_.x(),(int)center_.y());
    qDebug()<<tr("radius = %1").arg(radius_);
    for(int y=0;y<picture->height();y++)
    {
        for(int x=0;x<picture->width();x++)
        {
            QPoint current_pixcel_pos = QPoint(x,y)-center;
            int distance = current_pixcel_pos.x()*current_pixcel_pos.x()+current_pixcel_pos.y()*current_pixcel_pos.y();
            if((distance > (radius_*radius_))&&(distance <(radius_+6)*radius_+6))
            {
                pixcel_array[x+y*(picture->width())] = black;
            }
            else if((distance >= ((radius_+5)*(radius_+5))))
            {
                pixcel_array[x+y*(picture->width())] = white;
            }
        }

    }
//    设置透明背景的代码
//    QPixmap free = QPixmap::fromImage(*picture);
//    QBitmap mask= free.createMaskFromColor(QColor(255,255,255),Qt::MaskInColor);    //创建白色像素的掩码 位图
//    free.setMask(mask);
//    free.save("cycle.png","PNG",100);
    show_cycle_ = false;
    pScene->ShowCycle(show_cycle_);
    picture->save("temp1.png","PNG",100);

}

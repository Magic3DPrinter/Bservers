#include "bserverwindow.h"
#include "ui_bserverwindow.h"


BserverWindow::BserverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BserverWindow)
{
    ui->setupUi(this);
    x.setText("This is the picture show label");
    y.setText("This is the 3D printer show label");
    z.setText("This is the order show label");

    printer1 = new controlPanel();
    printer2 = new controlPanel();
    printer3 = new controlPanel();
    printer4 = new controlPanel();
    allPrinter = new QGridLayout();
    allPrinter->addWidget(printer1,0,0);
    allPrinter->addWidget(printer2,0,1);
    allPrinter->addWidget(printer3,1,0);
    allPrinter->addWidget(printer4,1,1);
    allPrinterFrame = new QFrame();
    allPrinterFrame->setMaximumHeight(700);
    allPrinterFrame->setLayout(allPrinter);
    imageProcess = new ImagePrinter();
    ui->vBoxLayout->addWidget(allPrinterFrame);
    ui->vBoxLayout->addWidget(imageProcess);
    ui->vBoxLayout->addWidget(&z);
    allPrinterFrame->hide();
    imageProcess->show();
    z.hide();
}

BserverWindow::~BserverWindow()
{
    delete ui;
}

void BserverWindow::on_PictureBtn_clicked()     //图片栏
{
    allPrinterFrame->hide();
    imageProcess->show();
    z.hide();
}

void BserverWindow::on_PrinterBtn_clicked()     //打印机栏
{
   allPrinterFrame->show();
   imageProcess->hide();
   z.hide();
}

void BserverWindow::on_OrderBtn_clicked()       //订单栏
{
    allPrinterFrame->hide();
    imageProcess->hide();
    z.show();
}

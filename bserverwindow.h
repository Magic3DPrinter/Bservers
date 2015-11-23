#ifndef BSERVERWINDOW_H
#define BSERVERWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "./ImageProcesser/imageprinter.h"
#include "./PrinterPanel/controlpanel.h"

namespace Ui {
class BserverWindow;
}

class BserverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BserverWindow(QWidget *parent = 0);
    ~BserverWindow();

private slots:
    void on_PictureBtn_clicked();
    void on_PrinterBtn_clicked();
    void on_OrderBtn_clicked();

private:
    Ui::BserverWindow *ui;
    controlPanel* printer1;
    controlPanel* printer2;
    controlPanel* printer3;
    controlPanel* printer4;
    QGridLayout* allPrinter;
    QFrame * allPrinterFrame;

    ImagePrinter* imageProcess;

    QLabel x;
    QLabel y;
    QLabel z;
};

#endif // BSERVERWINDOW_H

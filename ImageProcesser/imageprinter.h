#ifndef IMAGEPRINTER_H
#define IMAGEPRINTER_H

#include <QWidget>
#include <QFileInfo>

//openCV include
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include "fontdialog.h"
#include "pgraphicsscene.h"
#include "./PrintPos/widget.h"
#include "./SliceEngine/fffProcessor.h"
#include "./SliceEngine/settings.h"

namespace Ui {
class ImagePrinter;
}

class ImagePrinter : public QWidget
{
    Q_OBJECT

public:
    explicit ImagePrinter(QWidget *parent = 0);
    ~ImagePrinter();
signals:
    void Sig_preHeart();

public slots:
    void slotUpdateMB();
    void on_openPix_clicked();
    void on_printPix_clicked();
    void on_savePix_clicked();
    void on_BinarySlider_sliderMoved(int position);


    void on_addText_clicked();
    void addText();
    void on_preHeart_clicked();
    void on_fill_clicked(bool checked);
    void on_pushButton_3_clicked();
    void on_p_height_returnPressed();
    void on_p_width_returnPressed();

    void on_lineEdit_returnPressed();
    void on_BinarySlider_valueChanged(int value);
    void on_printPosbt_clicked();
    void on_mbList_activated(const QString &arg1);
private slots:
    void on_radiusLineEdit_editingFinished();

    void on_useRadius_clicked();

    void on_rebuildPicture_clicked();

private:
    Ui::ImagePrinter *ui;

    QList<QFileInfo> *fileInfo;
    QString pixSize;
    QPointF printCenter;
    Widget* printPos;
    pGraphicsScene* pScene;

    QString openFile;
    QTimer *recodeTime;

    unsigned int timeRun;

    QStringList printableList;

    bool stoped;
    bool connected;
    bool filled;
    bool imgfileLoaded;
    bool show_cycle_;
    QString printStatus;

    //image print
    QImage * free;
    QImage* grayImg;
    QImage currentImg;
    float scale;
    int grayscale;
    FontDialog* font_dialog;

    void ScalePicture(float scale);
    void GrayScalePicture(int grayscale);

    cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );
    QImage cvMatToQImage( const cv::Mat &inMat );
    void savePrintFile(QString);
    void DrawClcle(QString picture_path_,QPointF center_,int radius_);


    void Enable_User_Waiting_Cursor();
    void Disable_User_Waiting_Cursor();

};

#endif // IMAGEPRINTER_H

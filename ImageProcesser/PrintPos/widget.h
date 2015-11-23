#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mgraphicsscene.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString getPicSize();
    QPointF getPicPos();
    void loadFile(QString p);
private slots:
    void on_certen_clicked();
//    void on_debug_clicked();
    void on_comboBox_activated(const QString &arg1);
//    void on_load_clicked();

    void on_saveModel_clicked();

    void on_MBcomboBox_activated(const QString &arg1);

    void on_deleteMB_clicked();

signals:
    void Sig_updateMB();

private:
    mGraphicsScene* pScene;
    Ui::Widget *ui;
    QGraphicsView* view;


    void updateCombox();
};


#endif // WIDGET_H

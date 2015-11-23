#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QFont>

namespace Ui {
class FontDialog;
}

class FontDialog : public QDialog
{
    Q_OBJECT
signals:
    void Sig_addText();
public:
    explicit FontDialog(QWidget *parent = 0);
    ~FontDialog();
    QFont getFont(){return pfont;}
    QPoint getPos(){return pos;}
    QString getText();
private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_fontComboBox_activated(const QString &arg1);

    void on_certern_clicked();

private:
    Ui::FontDialog *ui;
    QFont pfont;
    QPoint pos;
};

#endif // FONTDIALOG_H

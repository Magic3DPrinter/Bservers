#include "fontdialog.h"
#include "ui_fontdialog.h"

FontDialog::FontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontDialog)
{
    ui->setupUi(this);

}

FontDialog::~FontDialog()
{
    delete ui;
}


void FontDialog::on_comboBox_activated(const QString &arg1) //font size
{
    pfont.setPixelSize(arg1.toInt());
}

void FontDialog::on_fontComboBox_activated(const QString &arg1)
{
    pfont.setFamily(arg1);
}

void FontDialog::on_certern_clicked()
{
    pfont.setPixelSize(ui->comboBox->currentText().toInt());
    pfont.setFamily(ui->fontComboBox->currentText());
    pos.setX(ui->lineEdit->text().toInt());
    pos.setY(ui->lineEdit_2->text().toInt());
    emit Sig_addText();
    this->close();
}

QString FontDialog::getText()
{
    return ui->textBrowser->toPlainText();
}

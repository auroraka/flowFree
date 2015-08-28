#include "settingform.h"
#include "ui_settingform.h"
#include "music.h"
#include <QMessageBox>

SettingForm::SettingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);

    //添加背景
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    this->setPalette(palette);

}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::on_About_button_clicked()
{
    ui->label->setText("By ytl");
}

void SettingForm::on_changeMusic_button_clicked()
{
    music.changeStatus();
    if (music.getStatus() == Open){
        ui->changeMusic_button->setText("关闭声音");
    }
    if (music.getStatus() == Close){
        ui->changeMusic_button->setText("打开声音");
    }
}

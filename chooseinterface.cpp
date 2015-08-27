#include "chooseinterface.h"
#include "switcher.h"
#include "ui_chooseinterface.h"

ChooseInterface::ChooseInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseInterface)
{
    ui->setupUi(this);
}

ChooseInterface::~ChooseInterface()
{
    delete ui;
}

void ChooseInterface::on_back_button_clicked()
{
    switcher.showInterface("welcome");
}

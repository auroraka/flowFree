#include "designinterface.h"
#include "switcher.h"
#include "ui_designinterface.h"

DesignInterface::DesignInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignInterface)
{
    ui->setupUi(this);
}

DesignInterface::~DesignInterface()
{
    delete ui;
}

void DesignInterface::on_back_button_clicked()
{
    switcher.showInterface("welcome");
}

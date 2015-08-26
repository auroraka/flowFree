#include "designinterface.h"
#include "ui_designInterface.h"

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

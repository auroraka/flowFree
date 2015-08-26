#include "welcomeinterface.h"
#include "ui_welcomeinterface.h"

WelcomeInterface::WelcomeInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeInterface)
{
    ui->setupUi(this);
}

WelcomeInterface::~WelcomeInterface()
{
    delete ui;
}

#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include <QWidget>

namespace Ui {
class WelcomeInterface;
}

class WelcomeInterface : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeInterface(QWidget *parent = 0);
    ~WelcomeInterface();

private:
    Ui::WelcomeInterface *ui;
};

#endif // WELCOMEINTERFACE_H

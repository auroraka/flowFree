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

private slots:

    void on_goIntoGame_button_clicked();

    void on_designGame_button_clicked();

    void on_loadGame_button_clicked();

    void on_setting_button_clicked();

    void on_help_button_clicked();


private:
    Ui::WelcomeInterface *ui;
};

#endif // WELCOMEINTERFACE_H

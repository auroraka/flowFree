#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include "textinfo.h"
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
signals:
    void sendTextInfo(TextInfo text,int level,int id);
private slots:

    void on_goIntoGame_button_clicked();

    void on_designGame_button_clicked();

    void on_loadGame_button_clicked();

    void on_setting_button_clicked();

    void on_help_button_clicked();


    void on_exit_button_clicked();

private:
    Ui::WelcomeInterface *ui;
};

#endif // WELCOMEINTERFACE_H

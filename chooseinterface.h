#ifndef CHOOSEINTERFACE_H
#define CHOOSEINTERFACE_H

#include <QWidget>

namespace Ui {
class ChooseInterface;
}

class ChooseInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseInterface(QWidget *parent = 0);
    ~ChooseInterface();

private slots:

    void on_back_button_clicked();

private:
    Ui::ChooseInterface *ui;
};


#endif // CHOOSEINTERFACE_H

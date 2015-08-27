#ifndef CHOOSEINTERFACE_H
#define CHOOSEINTERFACE_H

#include "textinfo.h"
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
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void loadGame(int level,int id);

signals:
    sendTextInfo(TextInfo text,int level,int id);

private slots:

    void on_back_button_clicked();

private:
    Ui::ChooseInterface *ui;
};


#endif // CHOOSEINTERFACE_H

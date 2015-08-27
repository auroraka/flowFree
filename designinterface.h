#ifndef DESIGNINTERFACE_H
#define DESIGNINTERFACE_H

#include "drawer.h"
#include "gameinfo.h"
#include "textinfo.h"
#include <QWidget>

namespace Ui {
class DesignInterface;
}

class DesignInterface : public QWidget
{
    Q_OBJECT

public:
    explicit DesignInterface(QWidget *parent = 0);
    ~DesignInterface();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void reInit();

private slots:
    void on_back_button_clicked();


    void on_radioButton_5_5_clicked();

    void on_radioButton_6_6_clicked();

    void on_radioButton_7_7_clicked();


    void on_store_button_clicked();


    void on_clear_button_clicked();

private:
    Ui::DesignInterface *ui;
    GameInfo game;
    Drawer *drawer;
    int chooseSource;
    int sourceColor;
    QPoint movePoint;
    int haveMovePoint;
};

#endif // DESIGNINTERFACE_H

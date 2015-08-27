#ifndef DESIGNINTERFACE_H
#define DESIGNINTERFACE_H

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

private slots:
    void on_back_button_clicked();

private:
    Ui::DesignInterface *ui;
};

#endif // DESIGNINTERFACE_H

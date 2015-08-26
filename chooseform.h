#ifndef CHOOSEFORM_H
#define CHOOSEFORM_H

#include "gameinterface.h"
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QDialog>

class chooseForm : public QDialog
{
    Q_OBJECT
public:
    explicit chooseForm(QWidget *parent = 0);

signals:

public slots:
    void chooseDone();
private:
    QPushButton button;
    QRadioButton radio5,radio6,radio7,radio8,radio9,radio10,radio11,radio12;
};

#endif // CHOOSEFORM_H

#ifndef SETTINGFORM_H
#define SETTINGFORM_H


#include <QDialog>

namespace Ui {
class SettingForm;
}

class SettingForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = 0);
    ~SettingForm();

private slots:
    void on_About_button_clicked();

    void on_changeMusic_button_clicked();

private:
    Ui::SettingForm *ui;
};

#endif // SETTINGFORM_H

#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>

class QPushButton;
class QFileDialog;
class QHBoxLayout;
class QVBoxLayout;

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    SettingWindow();

public slots:
    void setArduinoDirectory();
private:
    QPushButton* ADSettingButton;
    QFileDialog* ADDialog;
    QHBoxLayout* mainLayout;

};

#endif // SETTINGWINDOW_H

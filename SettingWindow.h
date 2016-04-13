#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include "Option.h"

class QPushButton;
class QFileDialog;
class QHBoxLayout;
class QVBoxLayout;

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    SettingWindow();
    Option *option;
public slots:
    void setArduinoDirectory(QUrl);
private:
    QPushButton* ADSettingButton;
    QFileDialog* ADDialog;
    QHBoxLayout* mainLayout;

};

#endif // SETTINGWINDOW_H

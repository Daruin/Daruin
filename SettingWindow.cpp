#include "SettingWindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

SettingWindow::SettingWindow()
{
    ADSettingButton = new QPushButton("Setting Arduino Dialog");
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(ADSettingButton);
    setLayout(mainLayout);
    connect(ADSettingButton,SIGNAL(clicked()),this,SLOT(setArduinoDirectory()));

}

void SettingWindow::setArduinoDirectory(){

}

#include "SettingWindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

SettingWindow::SettingWindow()
{
    ADSettingButton = new QPushButton("Setting Arduino Dialog");
    mainLayout = new QHBoxLayout;
    ADDialog = new QFileDialog;
    mainLayout->addWidget(ADSettingButton);
    setLayout(mainLayout);
    connect(ADSettingButton,SIGNAL(clicked()),this,SLOT(setArduinoDirectory()));
    connect(ADDialog,SIGNAL(directoryUrlEntered(QUrl)),this,SLOT(setArduinoDirectory(QUrl)));
}

void SettingWindow::setArduinoDirectory(QUrl){

}

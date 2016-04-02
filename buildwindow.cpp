#include "buildwindow.h"
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

BuildWindow::BuildWindow()
{
    boardSelector = new QComboBox;
    serialPortSelector = new QComboBox;
    buildButton = new QPushButton("Build");
    compileButton = new QPushButton("Compile");

    selectorLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    selectorLayout->addWidget(boardSelector);
    selectorLayout->addWidget(serialPortSelector);
    buttonLayout->addWidget(buildButton);
    buttonLayout->addWidget(compileButton);

    mainLayout->addLayout(selectorLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(compileButton,SIGNAL(clicked()),this,SLOT(Compile()));
    connect(buildButton,SIGNAL(clicked()),this,SLOT(Build()));

}

void BuildWindow::Compile(void){

}

void BuildWindow::Build(void){

}

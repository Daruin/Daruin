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

    selectorLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    selectorLayout->addWidget(boardSelector);
    selectorLayout->addWidget(serialPortSelector);
    mainLayout->addLayout(selectorLayout);
    mainLayout->addWidget(buildButton);

    setLayout(mainLayout);
}


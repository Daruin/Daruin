#include "Daruin.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <stdio.h>//

Daruin::Daruin(void)
{
	text = new QTextEdit;
	menubar = new QMenuBar;
	menuF = new QMenu("file");

	setCentralWidget(text);
	menubar->addMenu(menuF);
	setMenuBar(menubar);

	connect(menuF->addAction("new file") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menuF->addAction("open file") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menuF->addAction("save file") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menuF->addAction("save file with naming") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menuF->addAction("quit") , SIGNAL(triggered()) , this , SIGNAL(quit()));

	connect(menubar->addAction("compile") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("upload") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("board") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("serial monitor") , SIGNAL(triggered()) , this , SLOT(call()));
}

void Daruin::call(void)
{
	printf("This is a test.\n");
}

#include "Daruin.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "buildwindow.h"
#include <stdio.h>//This library is needed only during debug

Daruin::Daruin(void)
{
    textEditor = new QTextEdit;
    menubar = new QMenuBar;
    fileMenu = new QMenu("file");

    dialog = new QDialog;
    layout_h = new QHBoxLayout;
    layout_v = new QVBoxLayout;
    label = new QLabel("you haven't save this file yet.\nwill you save?");
    yesButton = new QPushButton("yes");
    noButton = new QPushButton("no");
    cancelButton = new QPushButton("cancel");
    fileDialog = new QFileDialog();

    fileName = new QString("");
    fileState = '\0';
    changeState = false;

    buildWindow = new BuildWindow();

    setCentralWidget(textEditor);
    menubar->addMenu(fileMenu);
    setMenuBar(menubar);

    layout_h->addWidget(yesButton);
    layout_h->addWidget(noButton);
    layout_h->addWidget(cancelButton);
    layout_v->addWidget(label);
    layout_v->addLayout(layout_h);
    dialog->setLayout(layout_v);
    dialog->setWindowTitle("question");

    connect(fileMenu->addAction("new file") , SIGNAL(triggered()) , this , SLOT(openNewFile()));
    connect(fileMenu->addAction("open file") , SIGNAL(triggered()) , this , SLOT(openExistedFile()));
    connect(fileMenu->addAction("save file") , SIGNAL(triggered()) , this , SLOT(saveFile()));
    connect(fileMenu->addAction("save file with naming") , SIGNAL(triggered()) , this , SLOT(saveFileWithName()));
    connect(fileMenu->addAction("quit") , SIGNAL(triggered()) , this , SIGNAL(quit()));

    connect(menubar->addAction("compile") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("upload") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("board") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("serial monitor") , SIGNAL(triggered()) , this , SLOT(call()));

    connect(textEditor , SIGNAL(textChanged()) , this , SLOT(change()));
    connect(yesButton , SIGNAL(clicked()) , this , SLOT(openFileWithSave()));
    connect(noButton , SIGNAL(clicked()) , this , SLOT(openFileWithoutSave()));
	connect(cancelButton , SIGNAL(clicked()) , dialog , SLOT(hide()));
    connect(fileDialog,SIGNAL(fileSelected(QString)),this,SLOT(openFileWithName(QString)));
    printf("test");
}

void Daruin::call(void)
{
    printf("This is a test.\n");
}

void Daruin::change(void)
{
    changeState = true;
    setWindowTitle("Daruin -" + *fileName + "*");
}

void Daruin::displayAskSaveDialog(void)
{
    if(changeState){
        dialog->move(500 , 300);
        dialog->show();
    } else {
        openFileWithoutSave();
    }
}

void Daruin::openNewFile(void)
{
    fileState = 'n';
    displayAskSaveDialog();
    printf("new_displayAskSaveDialog\n");
}

void Daruin::openExistedFile(void)
{
    fileState = 'e';
    displayAskSaveDialog();
    printf("exist_displayAskSaveDialog\n");
}

void Daruin::openFile(void)
{
    switch(fileState){
        case 'n' : {
            textEditor->clear();
            fileName->clear();
            break;
        }
        case 'e' : {
            displayAskFileNameDialog();
            break;
        }
    }
}

void Daruin::openFileWithSave(void)
{
    printf("yes\n");
    dialog->hide();
    saveFile();
    if(*fileName != NULL){
        openFile();
    }
}

void Daruin::openFileWithoutSave(void)
{
    printf("no\n");
    dialog->hide();
    openFile();
}

void Daruin::displayAskFileNameDialog(void)
{
    printf("open essentially\n");
    fileDialog->show();
}

void Daruin::openFileWithName(QString name)
{
	*fileName = name;
    currentFile = new QFile(name);
    if(currentFile->open(QIODevice::ReadOnly)){
        QTextStream in(currentFile);
        textEditor->setPlainText(in.readAll());
    } else {
        printf("Error: Can't open file");
    }
    setWindowTitle("Daruin - " + *fileName);
    fileDialog->hide();
    delete currentFile;
}

void Daruin::saveFile(void)
{
    if(fileName != QLatin1String("")){
        printf("save_normal\n");
        currentFile = new QFile(*fileName);
        if(currentFile->open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(currentFile);
            stream << textEditor->toPlainText();
            changeState = false;
        } else {
            printf("Error : Cannot Open File");
        }
        setWindowTitle("Daruin - " + *fileName);
        delete currentFile;
    }else{
        saveFileWithName();
    }
}

void Daruin::saveFileWithName(void)
{
    *fileName = QFileDialog::getSaveFileName();

    if(*fileName != NULL){
        saveFile();
    }
}

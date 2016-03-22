#include "Daruin.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <stdio.h>//This library is needed only during debug

Daruin::Daruin(void)
{
    textEditor = new QTextEdit;
    menubar = new QMenuBar;
    fileMenu = new QMenu("file");
    str = new QString;

    dialog = new QDialog;
    layout_h = new QHBoxLayout;
    layout_v = new QVBoxLayout;
    label = new QLabel;
    lineedit = new QLineEdit;
    yesButton = new QPushButton;
    noButton = new QPushButton("no");
    cancelButton = new QPushButton("cancel");

    fileName = new char[50];//I will modify "[50]" in the future.
    fileName[0] = '\0';
    fileState = '\0';
    changeState = false;
    saveState = true;

    setCentralWidget(textEditor);
    menubar->addMenu(fileMenu);
    setMenuBar(menubar);

    layout_h->addWidget(lineedit);
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
    connect(fileMenu->addAction("save file with naming") , SIGNAL(triggered()) , this , SLOT(displayAskSaveFileNameDialog()));
    connect(fileMenu->addAction("quit") , SIGNAL(triggered()) , this , SIGNAL(quit()));

    connect(menubar->addAction("compile") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("upload") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("board") , SIGNAL(triggered()) , this , SLOT(call()));
    connect(menubar->addAction("serial monitor") , SIGNAL(triggered()) , this , SLOT(call()));

    connect(textEditor , SIGNAL(textChanged()) , this , SLOT(change()));
    connect(cancelButton , SIGNAL(clicked()) , this , SLOT(close_dialog()));
    connect(noButton , SIGNAL(clicked()) , this , SLOT(openFileWithoutSave()));
}

void Daruin::call(void)
{
    printf("This is a test.\n");
}

void Daruin::change(void)
{
    changeState = true;
}

void Daruin::displayAskSaveDialog(void)
{
    yesButton->setText("yes");
    label->setText("you haven't save this file yet.\nwill you save?");
    lineedit->hide();
    noButton->show();
    connect(yesButton , SIGNAL(clicked()) , this , SLOT(openFileWithSave()));
    dialog->move(500 , 300);
    dialog->show();
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
    close_dialog();

    switch(fileState){
        case 'n' : {
            if(saveState) {
                saveFile();
                soState = 'n';
            }else {
                textEditor->clear();
                fileName[0] = '\0';
            }
            break;
        }
        case 'e' : {
            if(saveState) {
                saveFile();
                soState = 'e';
            } else {
                displayAskFileNameDialog();
            }
            break;
        }
    }
}

void Daruin::openFileWithSave(void)
{
    printf("yes\n");
    saveState = true;
    openFile();
}

void Daruin::openFileWithoutSave(void)
{
    printf("no\n");
    saveState = false;
    openFile();
}

void Daruin::displayAskFileNameDialog(void)
{
    printf("open essentially\n");
    fileState = 'o';
    yesButton->setText("open");
    lineedit->setText("");
    label->setText("please input the name of file which you want to open");
    lineedit->show();
    noButton->hide();
    connect(yesButton , SIGNAL(clicked()) , this , SLOT(openFileWithName()));
    dialog->move(500 , 300);
    dialog->show();
}

void Daruin::openFileWithName(void)
{
    FILE* fp;
    short word_num;

    str->clear();
    *str = lineedit->text();
    word_num = str->size();

    for(short i = 0  ;  i < word_num  ;  i++){
        fileName[i] = (str->at(i)).unicode();
    }
    fileName[word_num] = '\0';

    fp = fopen(fileName , "r");

    if(fp != NULL){
        char ch;

        str->clear();

        while(1){
            ch = fgetc(fp);
            if(ch != EOF)
                str->append(QChar::fromLatin1(ch));
            else
                break;
        }
        textEditor->setPlainText(*str);
        fclose(fp);
    }else{
        printf("fail to open this file\n");
    }
    close_dialog();
}

void Daruin::saveFile(void)
{
    if(fileName[0]){
        printf("save_normal\n");
        FILE* fp = fopen(fileName , "w");

        if(fp != NULL){
            int word_num;

            *str = textEditor->toPlainText();
            word_num = str->size();

            for(int i = 0  ;  i < word_num  ;  i++){
                fputc((str->at(i)).unicode() , fp);
            }

            fclose(fp);
            changeState = false;
            saveState = false;
        }else{
            printf("I cannot write on this file.\n");
        }
    }else{
        displayAskSaveFileNameDialog();
    }
}

void Daruin::displayAskSaveFileNameDialog(void)
{
    printf("save_name\n");
    fileState = 's';
    yesButton->setText("save");
    lineedit->setText("");
    label->setText("please input the name of file which you want to write on");
    lineedit->show();
    noButton->hide();
    connect(yesButton , SIGNAL(clicked()) , this , SLOT(saveFileWithName()));
    dialog->move(500 , 300);
    dialog->show();
}

void Daruin::saveFileWithName(void)
{
    short word_num;

    str->clear();
    *str = lineedit->text();
    word_num = str->size();

    for(short i = 0  ;  i < word_num  ;  i++){
        fileName[i] = (str->at(i)).unicode();
    }
    fileName[word_num] = '\0';

    saveFile();

    switch(soState){
    case 'n' : {
        close_dialog();
        textEditor->clear();
        fileName[0] = '\0';
        break;
    }
    case 'e' : {
        close_dialog();
        displayAskFileNameDialog();
        break;
    }
    default  : {
        close_dialog();
        break;
    }
    }
}

void Daruin::close_dialog(void)
{
    switch(fileState){
    case 'e' :
    case 'n' : disconnect(yesButton , SIGNAL(clicked()) , this , SLOT(openFileWithSave()));	break;
    case 'o' : disconnect(yesButton , SIGNAL(clicked()) , this , SLOT(openFileWithName()));		break;
    case 's' : disconnect(yesButton , SIGNAL(clicked()) , this , SLOT(saveFileWithName()));	break;
    }
    dialog->hide();
    soState = '\0';
}

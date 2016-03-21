#include "Daruin.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QChar>
#include <stdio.h>//This library is needed only during debug

Daruin::Daruin(void)
{
	text = new QTextEdit;
	menubar = new QMenuBar;
	menuF = new QMenu("file");
	str = new QString;
	file_name = new char[50];//I will modify "[50]" in the future.
	file_name[0] = '\0';

	setCentralWidget(text);
	menubar->addMenu(menuF);
	setMenuBar(menubar);

	connect(menuF->addAction("new file") , SIGNAL(triggered()) , this , SLOT(clear()));
	connect(menuF->addAction("open file") , SIGNAL(triggered()) , this , SLOT(open()));
	connect(menuF->addAction("save file") , SIGNAL(triggered()) , this , SLOT(save()));
	connect(menuF->addAction("save file with naming") , SIGNAL(triggered()) , this , SLOT(save_name()));
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

void Daruin::clear(void)
{
	text->clear();
}

void Daruin::open(void)
{
//in here, input file name.  but now, file name is readme.
	strcpy(file_name , "README.md");
	FILE* fp = fopen(file_name , "r");

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
		text->setPlainText(*str);
		fclose(fp);
	}else{
		printf("fail to open this file\n");
	}
}

void Daruin::save(void)
{
	if(file_name[0]){
		FILE* fp = fopen(file_name , "w");

		if(fp != NULL){
			int word_num;

			*str = text->toPlainText();
			word_num = str->size();

			for(int i = 0  ;  i < word_num  ;  i++){
				fputc((str->at(i)).unicode() , fp);
			}

			fclose(fp);
		}else{
			printf("I cannot write on this file.\n");
		}
	}else{
		save_name();
	}
}

void Daruin::save_name(void)
{
//in here, input file name.  but now, file name is readme.
	strcpy(file_name , "README.md");
	save();
}

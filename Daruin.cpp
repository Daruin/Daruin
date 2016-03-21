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
	text = new QTextEdit;
	menubar = new QMenuBar;
	menuF = new QMenu("file");
	str = new QString;

	dialog = new QDialog;
	layout_h = new QHBoxLayout;
	layout_v = new QVBoxLayout;
	label = new QLabel;
	lineedit = new QLineEdit;
	button_yes = new QPushButton;
	button_no = new QPushButton("no");
	button_can = new QPushButton("cancel");

	file_name = new char[50];//I will modify "[50]" in the future.
	file_name[0] = '\0';
	file_state = '\0';
	change_state = false;
	save_state = true;

	setCentralWidget(text);
	menubar->addMenu(menuF);
	setMenuBar(menubar);

	layout_h->addWidget(lineedit);
	layout_h->addWidget(button_yes);
	layout_h->addWidget(button_no);
	layout_h->addWidget(button_can);
	layout_v->addWidget(label);
	layout_v->addLayout(layout_h);
	dialog->setLayout(layout_v);
	dialog->setWindowTitle("question");

	connect(menuF->addAction("new file") , SIGNAL(triggered()) , this , SLOT(open1_new()));
	connect(menuF->addAction("open file") , SIGNAL(triggered()) , this , SLOT(open1_exist()));
	connect(menuF->addAction("save file") , SIGNAL(triggered()) , this , SLOT(save()));
	connect(menuF->addAction("save file with naming") , SIGNAL(triggered()) , this , SLOT(save_name1()));
	connect(menuF->addAction("quit") , SIGNAL(triggered()) , this , SIGNAL(quit()));

	connect(menubar->addAction("compile") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("upload") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("board") , SIGNAL(triggered()) , this , SLOT(call()));
	connect(menubar->addAction("serial monitor") , SIGNAL(triggered()) , this , SLOT(call()));

	connect(text , SIGNAL(textChanged()) , this , SLOT(change()));
	connect(button_can , SIGNAL(clicked()) , this , SLOT(close_dialog()));
	connect(button_no , SIGNAL(clicked()) , this , SLOT(open2_no()));
}

void Daruin::call(void)
{
	printf("This is a test.\n");
}

void Daruin::change(void)
{
	change_state = true;
}

void Daruin::open1(void)
{
//	if(change_state){
		button_yes->setText("yes");
		label->setText("you haven't save this file yet.\nwill you save?");
		lineedit->hide();
		button_no->show();
		connect(button_yes , SIGNAL(clicked()) , this , SLOT(open2_yes()));
		dialog->move(500 , 300);
		dialog->show();
//	}
}

void Daruin::open1_new(void)
{
	file_state = 'n';
	open1();
	printf("new_open1\n");
}

void Daruin::open1_exist(void)
{
	file_state = 'e';
	open1();
	printf("exist_open1\n");
}

void Daruin::open2(void)
{
	close_dialog();

	switch(file_state){
		case 'n' : {
			if(save_state)
				save();

			if(save_state == false){
				text->clear();
				file_name[0] = '\0';
			}else{
				so_state = 'n';
			}

			break;
		}
		case 'e' : {
			if(save_state)
				save();

			if(save_state == false){
				open3();
			}else{
				so_state = 'e';
			}

			break;
		}
	}
}

void Daruin::open2_yes(void)
{
	printf("yes\n");
	save_state = true;
	open2();
}

void Daruin::open2_no(void)
{
	printf("no\n");
	save_state = false;
	open2();
}

void Daruin::open3(void)
{
	printf("open essentially\n");
	file_state = 'o';
	button_yes->setText("open");
	lineedit->setText("");
	label->setText("please input the name of file which you want to open");
	lineedit->show();
	button_no->hide();
	connect(button_yes , SIGNAL(clicked()) , this , SLOT(open4()));
	dialog->move(500 , 300);
	dialog->show();
}

void Daruin::open4(void)
{
	FILE* fp;
	short word_num;

	str->clear();
	*str = lineedit->text();
	word_num = str->size();

	for(short i = 0  ;  i < word_num  ;  i++){
		file_name[i] = (str->at(i)).unicode();
	}
	file_name[word_num] = '\0';

	fp = fopen(file_name , "r");

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
	close_dialog();
}

void Daruin::save(void)
{
	if(file_name[0]){
		printf("save_normal\n");
		FILE* fp = fopen(file_name , "w");

		if(fp != NULL){
			int word_num;

			*str = text->toPlainText();
			word_num = str->size();

			for(int i = 0  ;  i < word_num  ;  i++){
				fputc((str->at(i)).unicode() , fp);
			}

			fclose(fp);
			change_state = false;
			save_state = false;
		}else{
			printf("I cannot write on this file.\n");
		}
	}else{
		save_name1();
	}
}

void Daruin::save_name1(void)
{
	printf("save_name\n");
	file_state = 's';
	button_yes->setText("save");
	lineedit->setText("");
	label->setText("please input the name of file which you want to write on");
	lineedit->show();
	button_no->hide();
	connect(button_yes , SIGNAL(clicked()) , this , SLOT(save_name2()));
	dialog->move(500 , 300);
	dialog->show();
}

void Daruin::save_name2(void)
{
	short word_num;

	str->clear();
	*str = lineedit->text();
	word_num = str->size();

	for(short i = 0  ;  i < word_num  ;  i++){
		file_name[i] = (str->at(i)).unicode();
	}
	file_name[word_num] = '\0';

	save();

	switch(so_state){
		case 'n' : {
			close_dialog();
			text->clear();
			file_name[0] = '\0';
			break;
		}
		case 'e' : {
			close_dialog();
			open3();
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
	switch(file_state){
		case 'e' :
		case 'n' : disconnect(button_yes , SIGNAL(clicked()) , this , SLOT(open2_yes()));	break;
		case 'o' : disconnect(button_yes , SIGNAL(clicked()) , this , SLOT(open4()));		break;
		case 's' : disconnect(button_yes , SIGNAL(clicked()) , this , SLOT(save_name2()));	break;
	}
	dialog->hide();
	so_state = '\0';
}

#ifndef DARUIN_H
#define DARUIN_H

#include <QMainWindow>

class QTextEdit;
class QMenuBar;
class QMenu;
class QString;
class QDialog;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class Daruin : public QMainWindow
{
	Q_OBJECT

public:
	Daruin(void);

signals:
	void quit(void);

public slots:
	void call(void);
	void change(void);
	void open1_exist(void);
	void open1_new(void);
	void open2_yes(void);
	void open2_no(void);
	void open4(void);
	void save(void);
	void save_name1(void);
	void save_name2(void);
	void close_dialog(void);

private:
	void open1(void);
	void open2(void);
	void open3(void);

	QTextEdit* text;
	QMenuBar* menubar;
    QMenu* fileMenu;
	QString* str;

	QDialog* dialog;
	QHBoxLayout* layout_h;
	QVBoxLayout* layout_v;
	QLabel* label;
	QLineEdit* lineedit;
    QPushButton* yesButton;
    QPushButton* noButton;
    QPushButton* cancelButton;

    char* fileName;
    char fileState;
    bool saveState;
    char soState;
    bool changeState;
};

#endif

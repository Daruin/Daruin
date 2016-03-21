#ifndef DARUIN_H
#define DARUIN_H

#include <QMainWindow>

class QTextEdit;
class QMenuBar;
class QMenu;
class QString;

class Daruin : public QMainWindow
{
	Q_OBJECT
public:
	Daruin(void);
signals:
	void quit(void);
public slots:
	void call(void);
	void clear(void);
	void open(void);
	void save(void);
	void save_name(void);
private:
	QTextEdit* text;
	QMenuBar* menubar;
	QMenu* menuF;
	QString* str;
	char* file_name;
};

#endif

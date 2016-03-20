#ifndef DARUIN_H
#define DARUIN_H

#include <QMainWindow>

class QTextEdit;
class QMenuBar;
class QMenu;

class Daruin : public QMainWindow
{
	Q_OBJECT
public:
	Daruin(void);
signals:
	void quit(void);
public slots:
	void call(void);
private:
	QTextEdit* text;
	QMenuBar* menubar;
	QMenu* menuF;
};

#endif

#ifndef DARUIN_H
#define DARUIN_H

#include <QMainWindow>

class QTextEdit;

class Daruin : public QMainWindow
{
	Q_OBJECT
public:
	Daruin(void);
private:
	QTextEdit* text;
};

#endif

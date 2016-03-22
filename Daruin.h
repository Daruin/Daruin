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
    void openExistedFile(void);
    void openNewFile(void);
    void openFileWithSave(void);
    void openFileWithoutSave(void);
    void openFileWithName(void);
    void saveFile(void);
    void displayAskSaveFileNameDialog(void);
    void saveFileWithName(void);
	void close_dialog(void);

private:
    void displayAskSaveDialog(void);
    void openFile(void);
    void displayAskFileNameDialog(void);

    QTextEdit* textEditor;
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

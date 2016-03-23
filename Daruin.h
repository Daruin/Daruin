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
class QPushButton;
class QFile;
class QTextStream;
class QFileDialog;

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
    void openFileWithName(QString name);
    void saveFile(void);
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
    QString* fileName;

    QFileDialog* fileDialog;
	QDialog* dialog;
	QHBoxLayout* layout_h;
	QVBoxLayout* layout_v;
	QLabel* label;
    QPushButton* yesButton;
    QPushButton* noButton;
    QPushButton* cancelButton;
    QFile* currentFile;

    char fileState;

    bool saveState;
    char soState;
    bool changeState;
};

#endif
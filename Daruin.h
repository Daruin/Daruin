#ifndef DARUIN_H
#define DARUIN_H

#include <QMainWindow>
#include "buildwindow.h"
#include "SettingWindow.h"

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
class BuildWindow;
class SettingWindow;

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
    void callBuilder(void);
    void showSettingWindow(void);

private:
    void displayAskSaveDialog(void);
    void openFile(void);
    void displayAskFileNameDialog(void);

    QTextEdit* textEditor;
	QMenuBar* menubar;
    QMenu* fileMenu;
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
    BuildWindow* buildWindow;
    SettingWindow* settingWindow;

    char fileState;
    bool changeState;
};

#endif

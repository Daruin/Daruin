#ifndef BUILDWINDOW_H
#define BUILDWINDOW_H

#include <QWidget>

class QComboBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class BuildWindow : public QWidget
{
    Q_OBJECT
public:
    BuildWindow();

private slots:
    void Compile();
    void Build();

private:
    QComboBox* boardSelector;
    QComboBox* serialPortSelector;
    QPushButton* compileButton;
    QPushButton* buildButton;
    QHBoxLayout* selectorLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* mainLayout;

};

#endif // BUILDWINDOW_H

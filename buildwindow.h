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

private:
    QComboBox* boardSelector;
    QComboBox* serialPortSelector;
    QPushButton* buildButton;
    QHBoxLayout* selectorLayout;
    QVBoxLayout* mainLayout;

};

#endif // BUILDWINDOW_H

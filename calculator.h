#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots :
    void numPressed();
    void mathButtonsPressed();
    void equalButtonPressed();
    void changeNumberSign();
    void clearOperations();

};
#endif // CALCULATOR_H

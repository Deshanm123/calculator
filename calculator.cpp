#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

double calVal = 0.0;
bool divTrigger ;
bool multiTrigger ;
bool addTrigger ;
bool subTrigger ;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->displayLineEdit->setText(QString::number(calVal));
    QPushButton *numButtons[10];
//    assigning signal and slot for each button
    for(int i=0;i<10;i++)
    {
        QString buttonName = "n"+QString::number(i)+"Btn";
//        getting buttons names and add them to the array
//        casting for a push button
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
//       qDebug() << numButtons[i];
//       when num click is released calling the function
        connect(numButtons[i],SIGNAL(released()),this,SLOT(numPressed()));
       }
//assinging signal and slots for math operation buttons
    connect( ui->addBtn,SIGNAL(released()),this,SLOT( mathButtonsPressed()) );
    connect(ui->substractBtn,SIGNAL(released()),this,SLOT( mathButtonsPressed()) );
    connect(ui->multiplyBtn,SIGNAL(released()),this,SLOT( mathButtonsPressed()) ) ;
    connect(ui->divisionBtn,SIGNAL(released()),this,SLOT( mathButtonsPressed()) );
//change positive and negative
    connect(ui->changeSignBtn,SIGNAL(released()),this,SLOT(changeNumberSign()) );
//    equal button
    connect(ui->equalBtn,SIGNAL(released()),this,SLOT(equalButtonPressed()));
//clear button
    connect(ui->clearBtn,SIGNAL(released()),this,SLOT(clearOperations()));

}
Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numPressed(){
//    sender is going to return a pointer to the button that have pressed
    QPushButton *pressedButton  = (QPushButton *)sender();
//    get the number of the clicked Qbutton
    QString buttonStoredValue  = pressedButton->text();
    QString displayedValue = ui->displayLineEdit->text();
    if(displayedValue.toDouble()==0||displayedValue.toDouble()==0.0){
        ui->displayLineEdit->setText(buttonStoredValue);
    }else{
//        concatinating of values
        QString newValueString =   displayedValue+ buttonStoredValue;
        double  newValueDouble = newValueString.toDouble();
        ui->displayLineEdit->setText(QString::number(newValueDouble,'g',16));
    }
}

void Calculator::mathButtonsPressed(){
    divTrigger = false;
    multiTrigger = false;
    addTrigger = false;
    subTrigger = false;
//    retriving value from display
    QString displayVal = ui->displayLineEdit->text();
    calVal = displayVal.toDouble();
//    check the sender which button actually clicked on
//    casting to apush  button
    QPushButton *button = (QPushButton *)sender();
    QString buttonStoredValue = button ->text();

//    QString::compare will only return zero if the string passed to it and the
//    string it is called on are equal.
//    Qstring::operator== returns true if the strings are equal otherwise, false.

    if(QString::compare(buttonStoredValue,"/",Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(buttonStoredValue,"*",Qt::CaseInsensitive) == 0){
         multiTrigger = true;
    }else if(QString::compare(buttonStoredValue,"+",Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else{
        subTrigger = true;
    }
    ui->displayLineEdit->setText(" ");
}
void Calculator::equalButtonPressed(){
    double solution = 0.0 ;
    QString displayVal = ui->displayLineEdit->text();
    double  displayValDouble = displayVal.toDouble();
    if(addTrigger||subTrigger||multiTrigger||divTrigger){
        if(addTrigger){
            solution = calVal+displayValDouble;
//            qDebug() << solution;
        }
        else if(subTrigger){
             solution = calVal-displayValDouble;
        }
        else if(multiTrigger){
            solution = calVal * displayValDouble;
        }else{
            solution = calVal/displayValDouble;
        }
      ui->displayLineEdit->setText(QString::number(solution));
    }
}

void::Calculator::changeNumberSign(){
//    getting display value
    QString displayVal = ui -> displayLineEdit -> text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double displayValDouble = displayVal.toDouble();
        double displayValSign = displayValDouble * -1;
        ui->displayLineEdit->setText(QString::number(displayValSign));
    }
}

void::Calculator::clearOperations(){
    calVal = 0.0;
    ui->displayLineEdit->setText(QString::number(calVal));
}

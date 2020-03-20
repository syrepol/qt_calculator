#include "calculator.h"
#include "ui_calculator.h"

const double defaultVal = 0.0;
double calcVal = 0.0;
bool addTrigger = false;
bool subTrigger = false;
bool multTrigger = false;
bool divTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    const int amountOfNumButtons = 10;

    QPushButton *numButtons[amountOfNumButtons];
    for (int i = 0; i < amountOfNumButtons; i++) {
        QString btnName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumButtonPressed()));
    }

    connect(Calculator::findChild<QPushButton *>("Add"), SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(Calculator::findChild<QPushButton *>("Subtract"), SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(Calculator::findChild<QPushButton *>("Multiply"), SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(Calculator::findChild<QPushButton *>("Divide"), SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(Calculator::findChild<QPushButton *>("Equals"), SIGNAL(released()), this, SLOT(EqualsButtonPressed()));

    connect(Calculator::findChild<QPushButton *>("ChangeSign"), SIGNAL(released()), this, SLOT(ChangeSignButtonPressed()));

    connect(Calculator::findChild<QPushButton *>("Clear"), SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumButtonPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    QString displayVal = ui->Display->text();

    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText(btnVal);
    } else {
        QString newVal = displayVal + btnVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed() {
    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();

    if (QString::compare(btnVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if (QString::compare(btnVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    } else if (QString::compare(btnVal, "*", Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    } else if (QString::compare(btnVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualsButtonPressed() {
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (divTrigger || multTrigger || addTrigger || subTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger) {
            solution = calcVal / dblDisplayVal;
        }

        ui->Display->setText(QString::number(solution));
    }
}

void Calculator::ChangeSignButtonPressed() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    ui->Display->setText(QString::number(dblDisplayVal * -1));
}

void Calculator::ClearButtonPressed() {
    ui->Display->setText(QString::number(defaultVal));
}

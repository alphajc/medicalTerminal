#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    init_widget();
    result = 0;//"yunsuanjieguo"
    lastCommand = "=";//"yunsuanfu"
    start = true;//"shuruzhuangtai"
}

Calculator::~Calculator()
{
    delete ui;
}

//数值‘0’槽函数
void Calculator::on_pushButton_13_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_13->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘1’槽函数
void Calculator::on_pushButton_9_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_9->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘2’槽函数
void Calculator::on_pushButton_10_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_10->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘3’槽函数
void Calculator::on_pushButton_11_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_11->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘4’槽函数
void Calculator::on_pushButton_5_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_5->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘5’槽函数
void Calculator::on_pushButton_6_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_6->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘6’槽函数
void Calculator::on_pushButton_7_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_7->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘7’槽函数
void Calculator::on_pushButton_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘8’槽函数
void Calculator::on_pushButton_2_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_2->text();
    ui->label->setText(ui->label->text()+input);
}

//数值‘9’槽函数
void Calculator::on_pushButton_3_clicked()
{
    if(start){
        ui->label->setText("");
        start = false;
    }
    QString input = ui->pushButton_3->text();
    ui->label->setText(ui->label->text()+input);
}

//运算符‘+’槽函数
void Calculator::on_pushButton_16_clicked()
{
    QString command = ui->pushButton_16->text();
    if(start){
            lastCommand = command;
    }else{
        double x = ui->label->text().toDouble();
        calculate(x);
        lastCommand = command;
        start = true;
    }
}

//运算符‘-’槽函数
void Calculator::on_pushButton_12_clicked()
{
    QString command = ui->pushButton_12->text();
    if(start){
        ui->label->setText(command);
        start = false;
    }else{
        double x = ui->label->text().toDouble();
        calculate(x);
        lastCommand = command;
        start = true;
    }
}

//运算符‘*’槽函数
void Calculator::on_pushButton_8_clicked()
{
    QString command = ui->pushButton_8->text();
    if(start){
        lastCommand = command;
    }else{
        double x = ui->label->text().toDouble();
        calculate(x);
        lastCommand = command;
        start = true;
    }
}

//运算符‘/’槽函数
void Calculator::on_pushButton_4_clicked()
{
    QString command = ui->pushButton_4->text();
    if(start){
        lastCommand = command;
    }else{
        double x = ui->label->text().toDouble();
        calculate(x);
        lastCommand = command;
        start = true;
    }
}

//运算符‘.’槽函数
void Calculator::on_pushButton_14_clicked()
{
    QString command = ui->pushButton_14->text();
    if(start){
        ui->label->setText("");
    }else{
        QString input = ui->pushButton_14->text();
        ui->label->setText(ui->label->text()+input);
    }
}

//运算符‘=’槽函数
void Calculator::on_pushButton_15_clicked()
{
    QString command = ui->pushButton_15->text();
    if(start){
        lastCommand = command;
    }else{
        double x = ui->label->text().toDouble();
        calculate(x);
        lastCommand = command;
        start = true;
    }
}

void Calculator::calculate(double x)
{
    if(lastCommand == "+") result += x;
    else if(lastCommand == "-") result -= x;
    else if(lastCommand == "*") result *= x;
    else if(lastCommand == "/") result /= x;
    else if(lastCommand == "=") result = x;
    ui->label->setText(QString::number(result));
}

void Calculator::init_widget()
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void Calculator::on_returnButton_clicked()
{
    hide();
}

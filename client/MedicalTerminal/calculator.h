#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
    void calculate(double);//"jisuanfangfa"
    void init_widget();

private slots:
    void on_pushButton_13_clicked();//数值‘0’槽函数

    void on_pushButton_9_clicked();//数值‘1’槽函数

    void on_pushButton_10_clicked();//数值‘2’槽函数

    void on_pushButton_11_clicked();//数值‘3’槽函数

    void on_pushButton_5_clicked();//数值‘4’槽函数

    void on_pushButton_6_clicked();//数值‘5’槽函数

    void on_pushButton_7_clicked();//数值‘6’槽函数

    void on_pushButton_clicked();//数值‘7’槽函数

    void on_pushButton_2_clicked();//数值‘8’槽函数

    void on_pushButton_3_clicked();//数值‘9’槽函数

    void on_pushButton_16_clicked();//运算符‘+’槽函数

    void on_pushButton_12_clicked();//运算符‘-’槽函数

    void on_pushButton_8_clicked();//运算符‘*’槽函数

    void on_pushButton_4_clicked();//运算符‘/’槽函数

    void on_pushButton_14_clicked();//运算符‘.’槽函数

    void on_pushButton_15_clicked();//运算符‘=’槽函数

    void on_returnButton_clicked();

private:
    double result;//运算结果
    QString lastCommand;//显示屏显示结果
    bool start;//计算器计算状态

private:
    Ui::Calculator *ui;
};

#endif // CALCULATOR_H

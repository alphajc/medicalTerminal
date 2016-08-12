#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "mainwidget.h"
#include <QCoreApplication>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    
private slots:
    void on_inPushButton_clicked();

    void on_outPushButton_clicked();

private:
    Ui::LoginWidget *ui;
    MainWidget *mainWidget;
};

#endif // LOGINWIDGET_H

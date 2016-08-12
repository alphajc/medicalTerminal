#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <stdio.h>
//#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
//#include <sys/ioctl.h>
#include <QTimer>
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace Ui {
class AlarmWidget;
}

class AlarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmWidget(QWidget *parent = 0);
    ~AlarmWidget();

public:
    void initUI();
    void initVariable();
    void handleAlarm(bool);
    void openBuzzer();
    void setUI(bool);

private:
    Ui::AlarmWidget *ui;
    QTimer* updateTimer;
    QTimer* durationTimer;

private:
    bool isStarted;//闹铃是否开启
    int fd;//打开/dev/pwm的文件描述符

    int hour,minute;//设置闹铃的时间
    int durationTime;//响铃持续时间


private slots:
    void timerUpdate();
    void on_comfirBtn_clicked();
    void on_cancleBtn_clicked();
    void closeBuzzer();

};

#endif // ALARMWIDGET_H

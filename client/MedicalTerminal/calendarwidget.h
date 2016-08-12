#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>

class QCalendarWidget;
class QGridLayout;

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    CalendarWidget();
    QString getTraditionMD(QDate);


private slots:
    void timeLook();
    void todayLook();

private:
    void Init();
    void setTodayFont();
    QGridLayout *layout;
    QCalendarWidget *calendar;
    QLabel *timeLabel;
    QLabel *traditionalTimeLabel;
    QDate date;
    QPushButton *returnButton;
    QPushButton *todayButton;
    QDate m_Today;

};


#endif

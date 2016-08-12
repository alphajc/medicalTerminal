#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QString>
#include <QDebug>

#include <time.h>

#include "bloodgauge.h"
#include "calculator.h"
#include "communication.h"
#include "doctorselect.h"
#include "patientselect.h"
#include "alarmwidget.h"
#include "calendarwidget.h"
#include "musicwidget.h"
#include "personalinformation.h"
#include "buildingpaintwidget.h"
#include "dayarrangewidget.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void create_connection();//如果有需要，则定义
    void init_widget();
    void recieve();

signals:
    void closed();

private slots:
    void on_PatientInfoButton_clicked();
    void on_DoctorIntrButton_clicked();
    void on_CalculatorButton_clicked();
    void on_MapButton_clicked();
    void on_PreviousButton_clicked();
    void on_NextButton_clicked();
    void show_time();
    void on_BloodButton_clicked();
    void close_widget();
    void on_personalIntrButton_clicked();
    void on_AlarmButton_clicked();
    void on_PlayerButton_clicked();
    void on_CalendarButton_clicked();
    void stateChanged(QAbstractSocket::SocketState state);
    void on_memorandumButton_clicked();


private:
    Ui::MainWidget  *ui;
    Calculator           calculator;
//    DoctorIntr          doctorIntr;
//    PatientInfo         patientInfo;
    DoctorSelect        doctorSelect;
    PatientSelect       patientSelect;
    BuildingPaintWidget  buildPaintWidget;
    BloodGauge      bloodGauge;
    AlarmWidget    alarmwidget;
    CalendarWidget calendarwidget;
    MusicWidget musicwidget;
    PersonalInformation personalInformation;
    DayArrangeWidget dayArrange;

    QPushButton     exitButton;

    QTimer                timer;
    time_t                  ticks;
    struct tm             *timenow;
    char                     currentTime[30];

};

#endif // MAINWIDGET_H

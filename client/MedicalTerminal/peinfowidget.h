#ifndef PEINFOWIDGET_H
#define PEINFOWIDGET_H

#include <QWidget>

#include "patientinfo.h"

namespace Ui {
class PEInfoWidget;
}

class PEInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PEInfoWidget(QWidget *parent = 0,float bloodSugar = 0.0, int maxBloodPressure = 0, int minBloodPressure = 0, int pulse = 0);
    ~PEInfoWidget();

public:
    void initUI();
//    void initVariable();
//    void setInfoValue(float bloodSugar,int maxBloodPressure,int minBloodPressure,int pulse);

private slots:
    void on_reTestBtn_clicked();

    void on_saveBtn_clicked();

    void on_exitButton_clicked();

private:
    Ui::PEInfoWidget        *ui;
    PatientInfo             patientInfo;
    QWidget                 *bloodGauge;

    int maxBloodPressure,minBloodPressure;//血压值
    int pulse;//脉搏值
    float bloodSugar;//血糖值

};

#endif // PEINFOWIDGET_H

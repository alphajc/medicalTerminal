#ifndef BLOOCGAUGE_H
#define BLOOCGAUGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <qdebug.h>
#include <qtextcodec.h>
#include <string.h>

#include "petestwidget.h"
#include "peinfowidget.h"

namespace Ui {
class BloodGauge;
}

class BloodGauge : public QWidget
{
    Q_OBJECT
    
public:
    explicit BloodGauge(QWidget *parent = 0);
    ~BloodGauge();
    
private:
    Ui::BloodGauge *ui;
    QVBoxLayout     *mainLayout;
    QPushButton     *startBtn;
    QTimer                *updateTimer;
    QTimer                *intervalTimer;
    bool                    hasAdc;

    int adc_fd;//文件描述符
    int maxBloodPressure,minBloodPressure;//血压值
    int pulse;//脉搏值
    float bloodSugar;//血糖值

    PETestWidget *petestwidget;
    PEInfoWidget *peinfowidget;

public:
    void initUI();
    void initVariable();

private slots:
    void on_backBtn_clicked();
    void on_startBtn_clicked();
    void updateData();
    void endTestData();
};

#endif // BLOOCGAUGE_H

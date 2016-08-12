#include "peinfowidget.h"
#include "ui_peinfowidget.h"

PEInfoWidget::PEInfoWidget(QWidget *parent,float bloodSugar, int maxBloodPressure, int minBloodPressure, int pulse) :
    QWidget(0),ui(new Ui::PEInfoWidget),bloodGauge(parent)
{
    ui->setupUi(this);
    this->bloodSugar = bloodSugar;
    this->maxBloodPressure = maxBloodPressure;
    this->minBloodPressure = minBloodPressure;
    this->pulse = pulse;
    initUI();

    show();
}

PEInfoWidget::~PEInfoWidget()
{
    delete ui;
}

void PEInfoWidget::initUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);//窗口无边框

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    ui->BS->display(QString::number(bloodSugar));
    ui->maxBP->display(QString::number(maxBloodPressure));
    ui->minBP->display(QString::number(minBloodPressure));
    ui->pulse->display(QString::number(pulse));
}

void PEInfoWidget::on_reTestBtn_clicked()
{
    bloodGauge->show();
    //延时
    QTime n=QTime::currentTime();
    QTime now;
    do{
        now=QTime::currentTime();
    }
    while(n.msecsTo(now)<=100);

    close();
}

void PEInfoWidget::on_saveBtn_clicked()
{
    QString data = trUtf8("血糖：%1 mmol/L\n血压最大值：%2Kpa\n血压最小值：%3Kpa\n脉搏：%4/min").arg(bloodSugar).arg(maxBloodPressure)
            .arg(minBloodPressure).arg(pulse);
    patientInfo.set_record(data);
    patientInfo.show();
}

void PEInfoWidget::on_exitButton_clicked()
{
    close();
}

#include "bloodgauge.h"
#include "ui_bloodgauge.h"

BloodGauge::BloodGauge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BloodGauge)
{
    ui->setupUi(this);
    initVariable();
    initUI();
}

BloodGauge::~BloodGauge()
{
    delete ui;
}

void BloodGauge::initUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);//窗口无边框

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    mainLayout = new QVBoxLayout(this);
    petestwidget = new PETestWidget(ui->frame);
    petestwidget->setTitle(tr("血压"));
    mainLayout->addWidget(petestwidget);
    ui->frame->setLayout(mainLayout);

}

void BloodGauge::initVariable()
{
    maxBloodPressure = 0;
    minBloodPressure = 250;
    pulse = 0;
    bloodSugar = 0.0;

    updateTimer = new QTimer(this);
    updateTimer->setInterval(500);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateData()));

    intervalTimer = new QTimer(this);
    intervalTimer->setInterval(10000);
    connect(intervalTimer,SIGNAL(timeout()),this,SLOT(endTestData()));
}
//返回
void BloodGauge::on_backBtn_clicked()
{
//    close(adc_fd);

    updateTimer->stop();
    intervalTimer->stop();
    petestwidget->clearVector();
    this->close();
}
//开始检测
void BloodGauge::on_startBtn_clicked()
{
    adc_fd = open("/dev/adc",0);
    hasAdc = TRUE;
    if(adc_fd < 0)
    {
        qDebug()<<"without ad";
        hasAdc = FALSE;
    }
    updateTimer->start();
    intervalTimer->start();
}
//存档
void BloodGauge::updateData()
{
    char buf[32];
    int value;
    memset(buf,0,32);

    if(hasAdc){
        if(read(adc_fd,buf,32) < 0)
        {
            qDebug()<<"read error!";
        }
        bool ok;
        value = tr(buf).toInt(&ok,10)%220 + 10;
    }
    else{
        value = qrand()%150+35;
        qDebug() << value;
    }
    if(value > maxBloodPressure)
    {
        maxBloodPressure = value;
    }
    if(value < minBloodPressure)
    {
        minBloodPressure = value;
    }

    petestwidget->addData(value);
    ui->label->setText(tr("当前值:%1").arg(value));

}
//结束测试
void BloodGauge::endTestData()
{
    updateTimer->stop();
    intervalTimer->stop();

    pulse = qrand()%120 + 30;
    bloodSugar = (float)(qrand()%50/10.0) + 3;
    peinfowidget = new PEInfoWidget(this,bloodSugar,maxBloodPressure,minBloodPressure,pulse);
    maxBloodPressure = 0;
    minBloodPressure = 250;
    pulse = 0;
    bloodSugar = 0.0;
    ui->label->setText(tr("当前值:"));
    petestwidget->clearVector();

    QTime n=QTime::currentTime();
    QTime now;
    do{
        now=QTime::currentTime();
    }
    while(n.msecsTo(now)<=500);

    hide();
}

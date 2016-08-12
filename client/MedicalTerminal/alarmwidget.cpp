#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmWidget)
{
    ui->setupUi(this);
    initVariable();
    initUI();
}

AlarmWidget::~AlarmWidget()
{
    delete ui;
}

void AlarmWidget::initVariable()
{
    ui->currenttimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));

    updateTimer =  new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    updateTimer->start(1000);

    durationTimer =  new QTimer(this);
    durationTimer->setSingleShot(true);
    connect(durationTimer, SIGNAL(timeout()), this, SLOT(closeBuzzer()));


    isStarted = false;
    hour = 0;
    minute = 0;
    durationTime = 0;
}

//控制闹铃的启动与关闭，flag为true时开启闹铃，否则关闭闹铃
void AlarmWidget::handleAlarm(bool flag)
{
    if(flag)
    {

        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("hh:mm");

        while(str.split(":").front().toInt() != hour
              || str.split(":").last().toInt()!= minute){

            if(! isStarted)//开启后又关闭闹钟
                break;

            QApplication::processEvents();  //防止ui假死
            time = QDateTime::currentDateTime();
            str = time.toString("hh:mm");

            if(str.split(":").front().toInt() == hour
                    && str.split(":").last().toInt()== minute){


                openBuzzer();
                durationTimer->start(durationTime);
                if(this->isHidden())
                {
                    this->show();
                }

                break;
            }
        }
    }else{
        setUI(true);
        durationTimer->start(0);//响应closeBuzzer()函数
    }

}

void AlarmWidget::openBuzzer()
{
//    fd = open("/dev/pwm",0);
//    if(fd < 0)
//    {
//        perror("open pwm error");
//        exit(1);
//    }
//    ioctl(fd, 1, 1000);//设置频率

    qDebug()<<"打开蜂鸣器";

}

void AlarmWidget::closeBuzzer()
{
//    if(fd >= 0)
//    {
//        ioctl(fd, 0);

//        ::close(fd);

//        fd = -1;
//    }
    qDebug()<<"关闭蜂鸣器";
    setUI(true);
}

//设置UI，flag为true时，表示当前可开启闹铃；flag为false时，表示当前已经开启闹铃
void AlarmWidget::setUI(bool flag)
{
    ui->hourSpinBox->setEnabled(flag);
    ui->minuteSpinBox->setEnabled(flag);
    ui->durationComboBox->setEnabled(flag);
    ui->comfirBtn->setText(flag ? tr("开启闹铃") : tr("取消闹铃"));

    if(flag)
    {
        ui->hourSpinBox->setValue(0);
        ui->minuteSpinBox->setValue(0);
        ui->durationComboBox->setCurrentIndex(0);
    }else
    {
        hour = ui->hourSpinBox->value();
        minute = ui->minuteSpinBox->value();
        durationTime = ui->durationComboBox->currentText().toInt()*60000;
    }

    isStarted = !flag;
}

void AlarmWidget::initUI()
{
    setWindowFlags(Qt::FramelessWindowHint);

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/bg05.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    ui->hourSpinBox->setPrefix("H: ");
    ui->hourSpinBox->setRange(0,23);
    ui->minuteSpinBox->setPrefix("M: ");
    ui->minuteSpinBox->setRange(0,59);
    ui->durationComboBox->addItem("1");
    ui->durationComboBox->addItem("2");
    ui->durationComboBox->addItem("3");
    ui->durationComboBox->addItem("4");
    ui->durationComboBox->addItem("5");

}


//更新当前时间
void AlarmWidget::timerUpdate()
{
    ui->currenttimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));

}

void AlarmWidget::on_comfirBtn_clicked()
{
    if(isStarted)
    {
        //取消闹铃
        setUI(true);
        handleAlarm(false);

    }else{
        //开启闹铃
        setUI(false);
        handleAlarm(true);

    }
}

void AlarmWidget::on_cancleBtn_clicked()
{
    if(isStarted){
        this->hide();
    }else
    {
        this->close();
    }

}


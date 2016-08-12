#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "recieveinformation.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    init_widget();
    recieve();

    create_connection();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::create_connection()
{
    connect(ui->exitButton, SIGNAL(clicked()),this, SLOT(close_widget()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(show_time()));
    connect(Communication::tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}
//初始化
void MainWidget::init_widget()
{
    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.png").scaled(this->size())));
    this->setPalette(backgroundPalette);

    Communication::init_tcp_socket();//生成套接字
    Communication::init_database();//初始化数据库
    setWindowFlags(Qt::FramelessWindowHint);

    timer.start(1000);
}
//接受数据
void MainWidget::recieve()
{
    new RecieveInformation(this);
    new RecieveInformation(this);
}
//显示时间
void MainWidget::show_time()
{
    qDebug() << "当前网络连接状态：" << Communication::tcpSocket->state();

    ticks = time(NULL);
    timenow = localtime(&ticks);
    strftime(currentTime, sizeof(currentTime), "%H:%M:%S %a", timenow);

    ui->TimeLabel->setText(tr(currentTime));
}
//患者信息
void MainWidget::on_PatientInfoButton_clicked()
{
//    patientInfo.show();
    patientSelect.init();
    patientSelect.show();
}
//医生简介
void MainWidget::on_DoctorIntrButton_clicked()
{
//    doctorIntr.show();
    doctorSelect.init();
    doctorSelect.show();
}

//计算器
void MainWidget::on_CalculatorButton_clicked()
{
    calculator.show();
}
//楼宇平面图
void MainWidget::on_MapButton_clicked()
{
    buildPaintWidget.show();
}

void MainWidget::on_PreviousButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_NextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//血糖血压
void MainWidget::on_BloodButton_clicked()
{
    bloodGauge.show();
}
//个人信息
void MainWidget::on_personalIntrButton_clicked()
{
    personalInformation.show();
}
//闹钟
void MainWidget::on_AlarmButton_clicked()
{
    alarmwidget.show();
}
//音乐播放器
void MainWidget::on_PlayerButton_clicked()
{
    musicwidget.show();
}

void MainWidget::on_CalendarButton_clicked()
{
    calendarwidget.show();
}

void MainWidget::stateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::ConnectedState){

    }
}

void MainWidget::close_widget()
{
    Communication::close_connection();//关闭套接字
    emit closed();
    close();
}

void MainWidget::on_memorandumButton_clicked()
{
    dayArrange.openArrange();
    dayArrange.show();
}

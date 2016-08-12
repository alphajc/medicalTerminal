#include "doctorselect.h"
#include "ui_doctorselect.h"
#include <QDebug>

DoctorSelect::DoctorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorSelect)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->doctorNameComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(otherDoctorThingsLook(QString)));  

}
//设置医生名
void DoctorSelect::setDoctorName()
{
//    qDebug("");
    QStringList name = db->selectDoctorsName();
    qDebug() << "setDoctor:" <<name;
    ui->doctorNameComboBox->insertItems(0,name);
}
//初始化
void DoctorSelect::init()
{
    db = Communication::db;

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    //设置成不能修改
    ui->doctorWorkLineEdit->setEnabled(false);
    ui->placeLineEdit->setEnabled(false);
    ui->timeTextEdit->setEnabled(false);
    ui->exprienceTextEdit->setEnabled(false);
    ui->doctorNameComboBox->clear();
    setDoctorName();
}

DoctorSelect::~DoctorSelect()
{
    delete ui;
}
//关闭
void DoctorSelect::on_doctorReturnPushButton_clicked()
{
    hide();
}
//根据医生名字匹配医生信息
void DoctorSelect::otherDoctorThingsLook(QString nowName)
{
    if(ui->doctorNameComboBox->count() > 0){
        QStringList doctor = db->selectDoctor(nowName);
        qDebug()<< "other_doctor:" << doctor;
        ui->doctorWorkLineEdit->setText(doctor.at(0));
        ui->placeLineEdit->setText(doctor.at(1));
        ui->timeTextEdit->setText(doctor.at(2));
        ui->exprienceTextEdit->setText(doctor.at(3));
    }
}

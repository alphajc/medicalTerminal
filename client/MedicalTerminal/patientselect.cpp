#include "patientselect.h"
#include "ui_patientselect.h"

PatientSelect::PatientSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientSelect)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    selectLineEdit = 0;
    ui->calendarWidget->hide();
    ui->totimeLookLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->againtimeLookLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->comeLookLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->totimeLookLineEdit->installEventFilter(this);
    ui->againtimeLookLineEdit->installEventFilter(this);
    ui->comeLookLineEdit->installEventFilter(this);
    connect(ui->calendarWidget,SIGNAL(selectionChanged()),this,SLOT(setLineEdit()));

    set_connection();
}

PatientSelect::~PatientSelect()
{
    delete ui;
}
//设置患者名字
void PatientSelect::setPatientName()
{
    qDebug() << "setpatientname";
    QStringList name = db->selectPatientsName();

    ui->nameLookComboBox->insertItems(0,name);
}
//初始化
void PatientSelect::init()
{
    db = Communication::db;

    ui->nameLookComboBox->clear();
    setPatientName();

}
//连接槽函数
void PatientSelect::set_connection()
{
    connect(ui->nameLookComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(otherThingsLook(QString)));
}
//根据患者名字显示其他信息
void PatientSelect::otherThingsLook(QString nowName)
{
    if(ui->nameLookComboBox->count() > 0){
        QStringList patient = db->selectPatient(nowName);
        qDebug() << patient.size();
        ui->sexLookLineEdit->setText(patient.at(0));
        ui->ageLookLineEdit->setText(patient.at(1));
        ui->workLookLineEdit->setText(patient.at(2));
        ui->comeLookLineEdit->setText(patient.at(3));
        ui->adressLookLineEdit->setText(patient.at(4));
        ui->allergyLookLineEdit->setText(patient.at(5));
        ui->againtimeLookLineEdit->setText(patient.at(6));
        ui->totimeLookLineEdit->setText(patient.at(7));
        ui->histroyLookLineEdit->setText(patient.at(8));
    }
}
//退出
void PatientSelect::on_returnButton_clicked()
{
    hide();
}
//修改患者信息
void PatientSelect::on_commitButton_clicked()
{
    db->updatePatient(ui->nameLookComboBox->currentText(),
            ui->sexLookLineEdit->text(),
            ui->ageLookLineEdit->text(),
            ui->workLookLineEdit->text(),
            ui->comeLookLineEdit->text(),
            ui->adressLookLineEdit->text(),
            ui->allergyLookLineEdit->text(),
            ui->againtimeLookLineEdit->text(),
            ui->totimeLookLineEdit->text(),
            ui->histroyLookLineEdit->text());

    ui->successLabel->setText("修改成功!");

    //to do: send to server
    QString message = "2&" + ui->nameLookComboBox->currentText() +"&"+ ui->sexLookLineEdit->text() +"&"+ ui->ageLookLineEdit->text() +"&"+
                      ui->workLookLineEdit->text() +"&"+ ui->comeLookLineEdit->text() +"&"+ ui->adressLookLineEdit->text() +"&"+
                      ui->allergyLookLineEdit->text() +"&"+ ui->againtimeLookLineEdit->text() +"&"+ ui->totimeLookLineEdit->text() +"&"+
                      ui->histroyLookLineEdit->text();
    SendInformation *infor = new SendInformation();
    infor->sendinformation(message);
    delete infor;
}
//过滤器的监听事件
bool PatientSelect::eventFilter(QObject *watched, QEvent *event)
{
     if (watched==ui->againtimeLookLineEdit)
     {
          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {
                selectLineEdit = 0;
                ui->calendarWidget->show();
          }
     }
     else if (watched==ui->comeLookLineEdit)
     {
         if (event->type()==QEvent::FocusIn)
         {
               selectLineEdit = 1;
               ui->calendarWidget->show();
         }
     }
     else if (watched==ui->totimeLookLineEdit)
     {
         if (event->type()==QEvent::FocusIn)
         {
               selectLineEdit = 2;
               ui->calendarWidget->show();
         }
     }

     return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}
//设置时间
void PatientSelect::setLineEdit()
{
    if(selectLineEdit == 0)
    {
         ui->againtimeLookLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(selectLineEdit == 1)
    {
        ui->comeLookLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(selectLineEdit == 2)
    {
        ui->totimeLookLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }

    ui->calendarWidget->hide();
}

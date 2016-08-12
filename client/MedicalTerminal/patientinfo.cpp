#include "patientinfo.h"
#include "ui_patientinfo.h"

PatientInfo::PatientInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfo)
{
    ui->setupUi(this);
    init_widget();
    connect(ui->enterPushButton,SIGNAL(clicked()), this,SLOT(sendMessage()));

    selectLineEdit = 0;
    ui->calendarWidget->hide();
    ui->totimeLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->againtimeLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->comeLineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->totimeLineEdit->installEventFilter(this);
    ui->againtimeLineEdit->installEventFilter(this);
    ui->comeLineEdit->installEventFilter(this);
    connect(ui->calendarWidget,SIGNAL(selectionChanged()),this,SLOT(setLineEdit()));
}

PatientInfo::~PatientInfo()
{
    delete ui;
}

void PatientInfo::create_connection()
{

}

void PatientInfo::init_widget()
{
    setWindowFlags(Qt::FramelessWindowHint);

    this->record = "";
}

void PatientInfo::set_record(QString record)
{
    this->record = record;

    ui->histroyLineEdit->setText(record+"\n");
}

void PatientInfo::sendMessage()
{
    message = "0&" + ui->nameLineEdit->text() +"&"+ ui->sexComboBox->currentText() +"&"+ ui->ageLineEdit->text() +"&"+
                      ui->workLineEdit->text() +"&"+ ui->comeLineEdit->text() +"&"+ ui->adressLineEdit->text() +"&"+
                      ui->allergyLineEdit->text() +"&"+ ui->againtimeLineEdit->text() +"&"+ ui->totimeLineEdit->text() +"&"+
                      ui->histroyLineEdit->toPlainText();

    qDebug() <<"ff:"<< ui->histroyLineEdit->toPlainText();
    //存入数据库
    Communication::db->insertPatientsDataWithoutId(message);

    //数据传输
    infor = new SendInformation();
    infor->sendinformation(message);
    ui->patientLabel->setText("成功!!!");
    delete infor;

}

void PatientInfo::on_exitButton_clicked()
{
    hide();
}


bool PatientInfo::eventFilter(QObject *watched, QEvent *event)
{
     if (watched==ui->againtimeLineEdit)
     {
          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {
                selectLineEdit = 0;
                ui->calendarWidget->show();
          }
     }
     else if (watched==ui->comeLineEdit)
     {
         if (event->type()==QEvent::FocusIn)
         {
               selectLineEdit = 1;
               ui->calendarWidget->show();
         }
     }
     else if (watched==ui->totimeLineEdit)
     {
         if (event->type()==QEvent::FocusIn)
         {
               selectLineEdit = 2;
               ui->calendarWidget->show();
         }
     }

     return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}

void PatientInfo::setLineEdit()
{
    if(selectLineEdit == 0)
    {
         ui->againtimeLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(selectLineEdit == 1)
    {
        ui->comeLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(selectLineEdit == 2)
    {
        ui->totimeLineEdit->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }

    ui->calendarWidget->hide();
}

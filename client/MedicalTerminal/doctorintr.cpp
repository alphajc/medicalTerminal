#include "doctorintr.h"
#include "ui_doctorintr.h"

DoctorIntr::DoctorIntr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorIntr)
{
    ui->setupUi(this);

    init_widget();
}

DoctorIntr::~DoctorIntr()
{
    delete ui;
}

void DoctorIntr::create_connection()
{

}

void DoctorIntr::init_widget()
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void DoctorIntr::on_doctorEnterPushButton_clicked()
{
    message = "1."+ ui->doctorNameLineEdit->text() +"."+ ui->doctorWorkLineEdit->text() +"."+ ui->placeComboBox->currentText() +"."+
                      ui->timeTextEdit->toPlainText() +"."+ ui->exprienceTextEdit->toPlainText();
    infor = new SendInformation();
    infor->sendinformation(message);
}

void DoctorIntr::on_doctorReturnPushButton_clicked()
{
    hide();
}

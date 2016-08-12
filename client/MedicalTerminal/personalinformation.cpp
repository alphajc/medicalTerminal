#include "personalinformation.h"
#include "ui_personalinformation.h"

PersonalInformation::PersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalInformation)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pixmap1(":/img/personalPicture.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap1));
    setPalette(palette);

    QPixmap pixmap2(":/img/personalReturn.png");
    ui->returnPushButton->setFixedSize(pixmap2.width(),pixmap2.height());
    ui->returnPushButton->setIcon(pixmap2);
    ui->returnPushButton->setIconSize(QSize(pixmap2.width(),pixmap2.height()));
    ui->returnPushButton->setToolTip("返回");

    initInformation();

}

PersonalInformation::~PersonalInformation()
{
    delete ui;
}
//初始化显示个人信息
void PersonalInformation::initInformation()
{
    ui->loginLabel->setText("");
    ui->nameLabel->setText("");
    ui->workLabel->setText("");
    ui->placeLabel->setText("");
    ui->timeLabel->setText("");
    ui->expLabel->setText("");
}
//退出
void PersonalInformation::on_returnPushButton_clicked()
{
    this->close();
}

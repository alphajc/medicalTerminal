#include "loginwidget.h"
#include "ui_loginwidget.h"
//
LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
        QCoreApplication::processEvents();
    } while (n.secsTo(now)<=1);//1为需要延时的秒数

    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);

    //setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint
                       | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                       | Qt::WindowMaximizeButtonHint);

    //setAutoFillBackground(true);
    QPixmap pixmap(":/img/login.png");
    //resize(pixmap.size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(palette);

    //测试代码
    this->ui->userLineEdit->setText("admin");
    this->ui->pwdLineEdit->setText("123");
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
//登入
void LoginWidget::on_inPushButton_clicked()
{
    QString user = this->ui->userLineEdit->text();
    QString pwd = this->ui->pwdLineEdit->text();
    if(user!="admin")
    {
        ui->errorUser->setText("用户名不存在！");
        ui->errorPwd->clear();
    }
    else if(user=="admin"&&pwd!="123")
    {
        ui->errorPwd->setText("密码错误！");
        ui->errorUser->clear();
    }
    else if(user=="admin"&&pwd=="123")
    {
        mainWidget = new MainWidget;
        mainWidget->show();
        connect(mainWidget, SIGNAL(closed()), this, SLOT(show()));
        hide();
    }

}

void LoginWidget::on_outPushButton_clicked()
{
    this->close();
}

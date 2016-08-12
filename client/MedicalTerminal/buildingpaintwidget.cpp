#include "buildingpaintwidget.h"
#include "ui_buildingpaintwidget.h"
#include <QPushButton>

BuildingPaintWidget::BuildingPaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuildingPaintWidget)
{
    ui->setupUi(this);
    this->setMinimumSize(240,320);
    this->setMaximumSize(240,320);
    initBuilding();
}

BuildingPaintWidget::~BuildingPaintWidget()
{
    delete ui;
}

void BuildingPaintWidget::initBuilding()
{
    setWindowFlags(Qt::FramelessWindowHint);
    QPushButton *exitButton = new QPushButton(this);
    exitButton->setIcon(QIcon(":/img/PLayer_back_24px_1184881_easyicon.net.png"));
    exitButton->setGeometry(215,2,20,20);
    exitButton->setFlat(true);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}


void BuildingPaintWidget::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::gray,1,Qt::SolidLine,Qt::RoundCap));

//    painter.setBrush( QBrush ( Qt :: green, Qt :: SolidPattern));

    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);

    painter.drawRect(30,15,20,80);//急诊楼
    painter.fillRect(QRect(35,35,10,40),QBrush(Qt::white));
    painter.drawText(15,55,"急诊楼");

    painter.drawRect(50,55,120,15);//门诊楼
    painter.fillRect(QRect(80,58,50,10),QBrush(Qt::white));
    painter.drawText(80,63,"门诊楼");

    painter.drawLine(80,35,80,15);
    painter.drawLine(150,35,150,15);
    painter.drawText(85,30,"就诊入口");

    QBrush brush(Qt::darkGreen,Qt::DiagCrossPattern);
    painter.setBrush(brush);
    painter.drawRoundRect(80,120,70,70);
    painter.drawText(90,150,"绿化带");

    painter.setBrush(QBrush((Qt::gray),Qt::NoBrush));
    painter.drawRect(170,68,30,100);//病房
    painter.fillRect(QRect(180,85,15,50),QBrush(Qt::white));
    painter.drawText(170,110,"病房");

    painter.drawRect(100,95,70,20);//传染科
    painter.fillRect(QRect(110,100,50,15),QBrush(Qt::white));
    painter.drawText(115,115,"传染科");

    painter.drawRect(0,95,50,20);//放射科
    painter.fillRect(QRect(8,100,30,10),QBrush(Qt::white));
    painter.drawText(8,110,"放射科");

    painter.drawRect(50,200,150,50);//医院主楼
    painter.fillRect(QRect(90,215,60,20),QBrush(Qt::white));
    painter.drawText(90,230,"医院主楼");

    painter.setPen(QPen(Qt::darkGreen,1,Qt::SolidLine,Qt::RoundCap));
    painter.drawLine(210,250,210,35);
    painter.drawLine(230,250,230,35);
    painter.drawText(214,80,"淮");
    painter.drawText(214,120,"海");
    painter.drawText(214,160,"西");
    painter.drawText(214,200,"路");

    painter.setPen(QPen(Qt::gray,1,Qt::SolidLine,Qt::RoundCap));
    painter.drawRect(0,135,50,50);//食堂
    painter.fillRect(QRect(15,150,15,30),QBrush(Qt::white));
    painter.drawText(15,165,"食堂");

    painter.drawRect(5,200,30,60);//办公楼
    painter.fillRect(QRect(12,213,15,30),QBrush(Qt::white));
    painter.drawText(0,230,"办公楼");

    painter.drawRect(5,260,80,30);//后勤综合楼
    painter.fillRect(QRect(25,267,40,20),QBrush(Qt::white));
    painter.drawText(10,280,"后勤综合楼");

    painter.drawRect(130,260,30,50);//垃圾站
    painter.fillRect(QRect(135,265,20,30),QBrush(Qt::white));
    painter.drawText(125,285,"垃圾站");

    painter.setPen(QPen(Qt::darkGreen,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawEllipse(205,60,5,5);
    painter.drawEllipse(203,86,5,5);
    painter.drawEllipse(204,99,5,5);
    painter.drawEllipse(206,110,5,5);
    painter.drawEllipse(207,130,5,5);
    painter.drawEllipse(203,150,5,5);
    painter.drawEllipse(207,165,5,5);
    painter.drawEllipse(205,200,5,5);

    //painter.setPen(QPen(QColor(90,250,170),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

}

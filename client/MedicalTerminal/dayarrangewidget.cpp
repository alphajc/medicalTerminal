#include "dayarrangewidget.h"
#include "ui_dayarrangewidget.h"

DayArrangeWidget::DayArrangeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DayArrangeWidget)
{
    ui->setupUi(this);

    QPalette backgroundPalette = this->palette();
    backgroundPalette.setBrush(QPalette::Background,QBrush(QPixmap(":/img/sbg.jpg").scaled(this->size())));
    this->setPalette(backgroundPalette);

    setWindowFlags(Qt::FramelessWindowHint);

}

DayArrangeWidget::~DayArrangeWidget()
{
    delete ui;
}

void DayArrangeWidget::openArrange()
{
    model = new QSqlTableModel(this);
    model->setTable("dayarrange");
    model->select();
    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(model);
}

//退出
void DayArrangeWidget::on_exitPushButton_clicked()
{
    this->close();
}
//删除日程
void DayArrangeWidget::on_deletePushButton_clicked()
{
    // 获取选中的行
    int curRow = ui->tableView->currentIndex().row();
     // 删除该行
    model->removeRow(curRow);

    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No || curRow>=model->rowCount())
    { // 如果不删除，则撤销
        model->revertAll();
    } else { // 否则提交，在数据库中删除该行
        model->submitAll();
    }
}
//增加日程
void DayArrangeWidget::on_addPushButton_clicked()
{
    // 获得表的行数
    int rowNum = model->rowCount();
    int id = 10;
    // 添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0), id);
    // 可以直接提交
    model->submitAll();
}

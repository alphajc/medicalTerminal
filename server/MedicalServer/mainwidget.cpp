#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    init_widget();
    init_socket();
    set_connection();
}

MainWidget::~MainWidget()
{
    delete ui;
}

//初始化套接字，并监听
void MainWidget::init_socket()
{
    server = new FortuneServer(db, this);

    if (!server->listen(QHostAddress::Any, 6666)) {
        qDebug() << server->errorString();
        close();
    }
}

//建立连接
void MainWidget::set_connection()
{
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tab_changed(int)));
    connect(server, SIGNAL(update_view()), this, SLOT(on_newPushButton_clicked()));
}

//初始化窗口
void MainWidget::init_widget()
{
    db = new ServerDataBase();

    ui->tabWidget->setTabText(0,tr("医生"));
    ui->tabWidget->setTabText(1,tr("患者"));

    doctorModel = new QSqlTableModel(this);
    patientModel = new QSqlTableModel(this);
    update_doctor_tab();
    update_patient_tab();
    tableView = ui->patientTable;
    model = patientModel;
}

void MainWidget::update_doctor_tab()
{
    doctorModel->setTable("doctor");
    doctorModel->select();
    // 设置编辑策略
    doctorModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->doctorTable->setModel(doctorModel);
}

void MainWidget::update_patient_tab()
{
        patientModel->setTable("patient");
        patientModel->select();
        // 设置编辑策略
        patientModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->patientTable->setModel(patientModel);
}

//更新
void MainWidget::on_newPushButton_clicked()
{
    patientModel->select();
    doctorModel->select();
}

//查询
void MainWidget::on_selectPushButton_clicked()
{
    QString name = ui->selectLineEdit->text();
    //根据姓名进行筛选，一定要使用单引号

    model->setFilter(QString("姓名 = '%1'").arg(name));
    model->select();
}

//删除
void MainWidget::on_deletePushButton_clicked()
{
    // 获取选中的行
    int curRow = tableView->currentIndex().row();
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

//撤销修改
void MainWidget::on_notUpdatePushButton_clicked()
{
     model->revertAll();
}

//提交记录
void MainWidget::on_submitPushButton_clicked()
{
    // 开始事务操作
    model->database().transaction();
    if (model->submitAll()) {

        QModelIndex sss = model->index(1,1);
        QVariant data = model->data(sss);
        qDebug() <<data.toString();



        model->database().commit(); //提交
    } else {
        model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

//添加患者记录
void MainWidget::on_addPushButton_clicked()
{
    // 获得表的行数
    int rowNum = model->rowCount();
    int id = db->selectPatientNum()+1;
    // 添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0), id);
    // 可以直接提交
    //model->submitAll();
}

//按患者姓名升序排列
void MainWidget::on_upPushButton_clicked()
{
    //id属性，即第0列，升序排列
    model->setSort(0, Qt::AscendingOrder);
    model->select();
}

//按患者姓名降序排列
void MainWidget::on_downPushButton_clicked()
{
    model->setSort(0, Qt::DescendingOrder);
    model->select();
}

void MainWidget::tab_changed(int index)
{
    if(index == 0){
        model = doctorModel;
        tableView = ui->doctorTable;
    }
    else if(index == 1){
        model = patientModel;
        tableView = ui->patientTable;
    }
}

#include "serverdatabase.h"

ServerDataBase::ServerDataBase()
{
    initDataBase();
}

void ServerDataBase::initDataBase()
{

    //设置连接mysql数据库信息
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    //选择并打开数据库
//    db.setDatabaseName("mtdb");
//    db.setPassword("123");
    db.setPort(3306);

    if(!db.open())
    {
        qDebug() <<"database open error!"<<endl;

        return;
    }

    QSqlQuery query;

    QString create_database = "create database if not exists mtdb character set utf8";
    query.prepare(create_database);
    if(!query.exec())
    {
        qDebug() <<"database mtdb create error!"<<endl;
        return;
    }

    db.close();
    db.setDatabaseName("mtdb");
    db.open();

    QString create_table_patients = "create table if not exists patient("
            "患者编号 integer primary key auto_increment not null,姓名 varchar(20), 性别 enum('男','女'), 年龄 varchar(10) ,"
            "职业 varchar(10) , 住院日期 varchar(10) , 家庭地址 varchar(10) , 过敏史 varchar(50) , 复诊日期 varchar(10) , 出诊日期 varchar(10) ,"
            " 病史记录 text)";
    QString create_table_doctors = "create table if not exists doctor(医生编号 integer primary key auto_increment not null,"
            "姓名 varchar(10) ,职称 varchar(10), 所在科室 varchar(10),坐诊时间 varchar(10) , 从业经验 varchar(50))";


    //创建患者表patients，如果已经存在则默认不创建
    query.prepare(create_table_patients);
    if(!query.exec())
    {
        qDebug() <<"table patients create error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

    //创建医生表doctors，如果已经存在则默认不创建
    query.prepare(create_table_doctors);
    if(!query.exec())
    {
        qDebug() <<"table doctors create error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

         qDebug() <<"init mtdb ok!"<<endl;
}

void ServerDataBase::insertDoctorsData(QString s)
{
    QSqlQuery query;
    QString insert_doctors = "insert into doctor("
            "姓名,职称,所在科室,坐诊时间,从业经验)"
            " values(?,?,?,?,?)";

    content = s.split("&");
    query.prepare(insert_doctors);
    query.addBindValue(content[1]);
    query.addBindValue(content[2]);
    query.addBindValue(content[3]);
    query.addBindValue(content[4]);
    query.addBindValue(content[5]);
    if(!query.exec())
    {
        qDebug() <<"insert doctors error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

    qDebug() <<"insert doctors ok!"<<endl;
}

void ServerDataBase::insertPatientsData(QString s)
{
    QSqlQuery query;
    QString insert_patients = "insert into "
            "patient(姓名,性别,年龄,职业,住院日期,家庭地址,过敏史,复诊日期,出诊日期,病史记录)"
            " values(?,?,?,?,?,?,?,?,?,?)";
    content = s.split("&");
    query.prepare(insert_patients);
    query.addBindValue(content[1]);
    query.addBindValue(content[2]);
    query.addBindValue(content[3]);
    query.addBindValue(content[4]);
    query.addBindValue(content[5]);
    query.addBindValue(content[6]);
    query.addBindValue(content[7]);
    query.addBindValue(content[8]);
    query.addBindValue(content[9]);
    query.addBindValue(content[10]);
    if(!query.exec())
    {
        qDebug() <<"insert patients error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

    qDebug() <<"insert patients ok!"<<endl;
}

int ServerDataBase::selectPatientNum()
{
    int num;
    QSqlQuery query;
    QString select_patients = "select MAX(患者编号) from patient";

    query.prepare(select_patients);

    if(!query.exec())
    {
        qDebug() <<"select patients error!"<<endl;
    }

    query.first();
    num = query.value(0).toInt();
    return num;
}

QStringList ServerDataBase::selectPatientsData()
{
    QStringList list;
    QSqlQuery query;
    QString select_patients = "select * from patient";

    query.prepare(select_patients);

    if(!query.exec())
    {
        qDebug() <<"select patients error!"<<endl;
    }

    while(query.next()){
        qDebug()<<query.value(1).toString();
        list.append(
            query.value(0).toString()+"&"+
            query.value(1).toString()+"&"+
            query.value(2).toString()+"&"+
            query.value(3).toString()+"&"+
            query.value(4).toString()+"&"+
            query.value(5).toString()+"&"+
            query.value(6).toString()+"&"+
            query.value(7).toString()+"&"+
            query.value(8).toString()+"&"+
            query.value(9).toString()+"&"+
            query.value(10).toString());
    }

    return list;
}

QStringList ServerDataBase::selectDoctorsData()
{
    QStringList list;
    QSqlQuery query;
    QString select_doctors = "select * from doctor";

    query.prepare(select_doctors);

    if(!query.exec())
    {
        qDebug() <<"select doctors error!"<<endl;
    }

    while(query.next()){
        list.append(
            query.value(0).toString()+"&"+
            query.value(1).toString()+"&"+
            query.value(2).toString()+"&"+
            query.value(3).toString()+"&"+
            query.value(4).toString()+"&"+
            query.value(5).toString());
    }
    qDebug() <<list;
    return list;
}

void ServerDataBase::updatePatient(QString name, QString sex, QString age, QString job, QString enter_datetime, QString address, QString allergic_hry, QString return_datetime, QString out_datetime, QString record)
{
    QSqlQuery query;
    QString select_patient = "update patient set 性别=?,年龄=?,职业=?,住院日期=?,家庭地址=?,过敏史=?,复诊日期=?,出诊日期=?,病史记录=? where 姓名=?";

    query.prepare(select_patient);
    query.addBindValue(sex);
    query.addBindValue(age);
    query.addBindValue(job);
    query.addBindValue(enter_datetime);
    query.addBindValue(address);
    query.addBindValue(allergic_hry);
    query.addBindValue(return_datetime);
    query.addBindValue(out_datetime);
    query.addBindValue(record);
    query.addBindValue(name);

    query.exec();
}



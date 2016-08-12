#include "clientdatabase.h"

ClientDataBase::ClientDataBase()
{

}

void ClientDataBase::initDataBase()
{
    clientdb = QSqlDatabase::addDatabase("QSQLITE");
    clientdb.setDatabaseName("client.db");

    if(!clientdb.open())
    {
        qDebug() <<"open client db error!";
    }


    QString create_table_patients = "create table if not exists patient("
            "患者编号 integer primary key autoincrement not null,姓名 varchar(20), 性别 varchar(20), 年龄 varchar(10) ,"
            "职业 varchar(10) , 住院日期 varchar(10) , 家庭地址 varchar(10) , 过敏史 varchar(50) , 复诊日期 varchar(10) , 出诊日期 varchar(10) ,"
            " 病史记录 text)";

    QString create_table_doctors = "create table if not exists doctor(医生编号 integer primary key autoincrement not null,"
            "姓名 varchar(10) ,职称 varchar(10) ,所在科室 varchar(10) , 坐诊时间 varchar(10) , 从业经验 varchar(50))";

    QString create_table_dayarrange = "create table if not exists dayarrange(事务编号 integer primary key autoincrement not null,事务内容 varchar(40))";

    //创建患者表patients，如果已经存在则默认不创建
    QSqlQuery query;
    query.prepare(create_table_patients);
    if(!query.exec())
    {
        qDebug() <<"table patient create error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

    qDebug() <<"SSSSSSSSS!"<<endl;

    //创建医生表doctors，如果已经存在则默认不创建
    query.prepare(create_table_doctors);
    if(!query.exec())
    {
        qDebug() <<"table doctor create error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }


    //创建事务表dayarrange，如果已经存在则默认不创建
    query.prepare(create_table_dayarrange);
    if(!query.exec())
    {
        qDebug() <<"table dayarrange create error!"<<endl;
        qDebug() <<query.lastError()<<endl;
        return;
    }

    qDebug() <<"init client db ok!"<<endl;

}

void ClientDataBase::insertDoctorsData(QString s)
{
    QSqlQuery query;
    QString insert_doctors = "insert into doctor(医生编号,姓名,职称,所在科室,坐诊时间,从业经验)"
            " values(?,?,?,?,?,?)";

    content = s.split("&");
    qDebug()<<content;
    query.prepare(insert_doctors);
    query.addBindValue(content[0]);
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

void ClientDataBase::insertPatientsDataWithoutId(QString s)
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

void ClientDataBase::insertPatientsDataWithId(QString s)
{
    QSqlQuery query;
    QString insert_patients = "insert into "
            "patient(患者编号,姓名,性别,年龄,职业,住院日期,家庭地址,过敏史,复诊日期,出诊日期,病史记录)"
            " values(?,?,?,?,?,?,?,?,?,?,?)";
    content = s.split("&");
    query.prepare(insert_patients);
    query.addBindValue(content[0]);
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

QStringList ClientDataBase::selectDoctorsName()
{

    QString name;
    QStringList namelist;
    QString select_doctors = "select 姓名 from doctor;";

    QSqlQuery query;
    query.prepare(select_doctors);
    query.exec();

    while(query.next())
    {

        name = query.value(0).toString();
        qDebug() <<query.value(0).toString()<<'\n'<<endl;
        namelist.append(name);
    }

    return namelist;
}

QStringList ClientDataBase::selectPatientsName()
{
    QSqlQuery query;
    QString name;
    QStringList namelist;
    QString select_patients = "select 姓名 from patient;";

    query.prepare(select_patients);
    query.exec();

    while(query.next())
    {
        name = query.value(0).toString();
        namelist.append(name);
    }

    return namelist;
}

QStringList ClientDataBase::selectDoctor(QString name)
{
    QSqlQuery query;
    QStringList doctor;
    qDebug()<<name;
    QString select_doctor = "select * from doctor where 姓名=?";

    query.prepare(select_doctor);
    query.addBindValue(name);

    query.exec();
    qDebug()<<query.lastError();

    if(query.first()){
        for(int i=2;i<=5;i++)
        {
                doctor.append(query.value(i).toString());
                qDebug() <<"inner:"<<query.value(i).toString();
        }
    }
    qDebug() << "doctorinfo:"<< doctor;
    return doctor;
}

QStringList ClientDataBase::selectPatient(QString name)
{
    qDebug() <<name;
    QSqlQuery query;
    QStringList patient;
    QString select_patient = "select * from patient where 姓名=?";

    query.prepare(select_patient);
    query.addBindValue(name);

    query.exec();
\
    if(query.first()){
        for(int i=2;i<=10;i++){
                patient.append(query.value(i).toString());
                qDebug() <<query.value(i).toString();
        }
    }
    return patient;
}

void ClientDataBase::updatePatient(QString name,QString sex,QString age,QString job,QString enter_datetime,
    QString address,QString allergic_hry,QString return_datetime,QString out_datetime,QString record)
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

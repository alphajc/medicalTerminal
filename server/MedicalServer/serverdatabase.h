#ifndef SERVERDATABASE_H
#define SERVERDATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

class ServerDataBase
{
public:
    ServerDataBase();
    void initDataBase();
    void insertDoctorsData(QString s);
    void insertPatientsData(QString s);
    int selectPatientNum();
    QStringList selectPatientsData();
    QStringList selectDoctorsData();
    void updatePatient(QString name, QString sex, QString age, QString job, QString enter_datetime,
         QString address, QString allergic_hry, QString return_datetime, QString out_datetime, QString record);
    void delData();
    void closeDB();
private:
   QSqlDatabase db;
   QStringList  content;
};

#endif // SERVERDATABASE_H

#ifndef CLIENTDATABASE_H
#define CLIENTDATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QSqlQuery>

class ClientDataBase
{
public:
    ClientDataBase();
    void initDataBase();
    void insertDoctorsData(QString s);
    void insertPatientsDataWithoutId(QString s);
    void insertPatientsDataWithId(QString s);
    QStringList selectDoctorsName();
    QStringList selectPatientsName();
    QStringList selectDoctor(QString name);
    QStringList selectPatient(QString name);
    void updatePatient(QString name, QString sex, QString age, QString job, QString enter_datetime,
        QString address, QString allergic_hry, QString return_datetime, QString out_datetime, QString record);
private:
    QSqlDatabase clientdb;
    QStringList content;
};

#endif // CLIENTDATABASE_H

#ifndef RECIEVEINFORMATION_H
#define RECIEVEINFORMATION_H

#include <QObject>
#include <QTcpSocket>
#include "clientdatabase.h"
#include "communication.h"

class RecieveInformation : public QObject
{
    Q_OBJECT
public:
    explicit RecieveInformation(QObject *parent = 0);
    void set_connection();
    void dealInfor(QString message);
public slots:
    void readMessage();

private:
    QString                 message;
    // 用来存放数据的大小信息
    quint16                 blockSize;
    QTcpSocket              *tcpsocket;
    ClientDataBase *db;
};

#endif // RECIEVEINFORMATION_H

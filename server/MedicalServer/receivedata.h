#ifndef RECEIVEDATA_H
#define RECEIVEDATA_H

#include <QObject>
#include <QTcpSocket>

#include "serverdatabase.h"

class ReceiveData : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveData(QObject *parent = 0);
    void insertInfor(QString s);
    void set_connection();
    void set_arguments(QTcpSocket *tcpsocket, ServerDataBase   *db);

signals:
    void update_view();

public slots:
    void readMessage();

private:
    QString          message;
    // 用来存放数据的大小信息
    quint16          blockSize;
    QTcpSocket       *tcpsocket;
    ServerDataBase   *db;
};

#endif // RECEIVEDATA_H

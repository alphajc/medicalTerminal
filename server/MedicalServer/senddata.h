#ifndef SENDDATA_H
#define SENDDATA_H

#include <QObject>
#include <QTcpSocket>

#include "serverdatabase.h"

class SendData : public QObject
{
    Q_OBJECT
public:
    explicit SendData(QObject *parent = 0);
    void set_arguments(QTcpSocket *tcpsocket, ServerDataBase   *db);

public slots:
    void sendMessage(QString information);

private:
    QTcpSocket          *tcpsocket;
    ServerDataBase   *db;
    quint16 blockSize;
};

#endif // SENDDATA_H

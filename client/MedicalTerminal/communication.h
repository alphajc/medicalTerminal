#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QTcpSocket>
#include <QAbstractSocket>
#include <QtNetwork>

#include "clientdatabase.h"

class Communication
{
public:
    static QTcpSocket   *tcpSocket;
    static ClientDataBase   *db;
    Communication();
    static void init_tcp_socket();
    static void init_database();
    static void close_connection();

signals:

public slots:
};

#endif // COMMUNICATION_H

#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>

#include "communication.h"
#include "serverdatabase.h"

class FortuneServer : public QTcpServer
{
    Q_OBJECT

public:
    FortuneServer(ServerDataBase  *db, QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

private:
    ServerDataBase   *db;

public slots:
    void emit_update();

signals:
    void update_view();
};

#endif

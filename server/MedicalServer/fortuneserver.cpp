#include "fortuneserver.h"

FortuneServer::FortuneServer(ServerDataBase *db, QObject *parent)
    : QTcpServer(parent),db(db)
{
}

void FortuneServer::incomingConnection(int socketDescriptor)
{
    Communication *thread = new Communication(socketDescriptor, db, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(update_view()), this, SLOT(emit_update()));
    thread->start();
}

void FortuneServer::emit_update()
{
    emit update_view();
}

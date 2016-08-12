#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QThread>
#include <QTcpSocket>

#include "receivedata.h"
#include "senddata.h"
#include "serverdatabase.h"

class Communication : public QThread
{
    Q_OBJECT
public:
    explicit Communication(int socketDescriptor, ServerDataBase *db, QObject *parent = 0);

protected:
    void run();

signals:
    void update_view();
    void error(QTcpSocket::SocketError socketError);

private:
    SendData       *sendData;
    ReceiveData    *receiveData;
    int             socketDescriptor;
    ServerDataBase *db;
    
public slots:
    void emit_update();
    void deal_state(QAbstractSocket::SocketState state);
};

#endif // COMMUNICATION_H

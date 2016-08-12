#include "communication.h"

QTcpSocket *Communication::tcpSocket = new QTcpSocket();
ClientDataBase *Communication::db = new ClientDataBase();

Communication::Communication()
{

}

void Communication::init_tcp_socket()
{
    // 取消已有的连接
    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1",6666);//服务器地址

}

void Communication::init_database()
{
    db->initDataBase();
}

void Communication::close_connection()
{
    tcpSocket->disconnectFromHost();
}


                                                                                             #include "senddata.h"

SendData::SendData(QObject *parent) :
    QObject(parent)
{

}

void SendData::set_arguments(QTcpSocket *tcpsocket, ServerDataBase *db)
{
    this->tcpsocket = tcpsocket;
    this->db = db;
}

void SendData::sendMessage(QString information)
{
    // 初始化数据大小信息为0
    blockSize = 0;
    // 用于暂存我们要发送的数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // 设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0;
    out << information;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    //block 数据包=数据大小（quint16）+实际数据
    connect(tcpsocket, SIGNAL(disconnected()),tcpsocket, SLOT(deleteLater()));
    tcpsocket->write(block);
}

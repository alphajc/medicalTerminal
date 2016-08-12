#include "sendinformation.h"

SendInformation::SendInformation()
{
    tcpSocket = Communication::tcpSocket;
}

SendInformation::~SendInformation()
{

}

void SendInformation::sendinformation(QString information)
{
     blockSize = 0;
    qDebug() << tcpSocket->state();
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

     connect(tcpSocket, SIGNAL(disconnected()),tcpSocket, SLOT(deleteLater()));
     tcpSocket->write(block);
}

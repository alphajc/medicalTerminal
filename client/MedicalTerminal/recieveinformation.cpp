#include "recieveinformation.h"

RecieveInformation::RecieveInformation(QObject *parent) :
    QObject(parent)
{
    tcpsocket = Communication::tcpSocket;
    db = Communication::db;

    set_connection();
}

void RecieveInformation::set_connection()
{
    connect(tcpsocket, SIGNAL(readyRead()),this,SLOT(readMessage()));
}

void RecieveInformation::dealInfor(QString message)
{
    QStringList infor;
    qDebug() <<"deal:"<<message;
    infor = message.split('`');
    if(infor.at(0) == tr("0")){
        for(int i = 1; i < infor.size(); ++i){
            //插入数据库（一条）
            db->insertPatientsDataWithId(infor.at(i));
        }
    }
    else if(infor.at(0) == tr("1")){
        for(int i = 1; i < infor.size(); ++i){
            //插入数据库（一条）
            db->insertDoctorsData(infor.at(i));
        }
    }
}

void RecieveInformation::readMessage()
{
    blockSize = 0;
    QDataStream in(tcpsocket);
    // 设置数据流版本，这里要和服务器端相同
    in.setVersion(QDataStream::Qt_4_6);
    // 如果是刚开始接收数据
    if (blockSize == 0) {
        //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
        qDebug() << "OK";
        if((blockSize = tcpsocket->bytesAvailable()) < (int)sizeof(quint16)) return;
        qDebug() << blockSize;
        message.clear();
        in >> blockSize;
        qDebug() << blockSize;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpsocket->bytesAvailable() < blockSize) return;
    // 将接收到的数据存放到变量中
    in >> message;

    //处理数据
    dealInfor(message);

}

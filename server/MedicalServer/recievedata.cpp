#include "receivedata.h"

ReceiveData::ReceiveData(QObject *parent):
     QObject(parent)
{

}

//判断应该写入的表格
void ReceiveData::insertInfor(QString s)
{
    if(s.split("&")[0] == QObject::tr("0"))
    {
        db->insertPatientsData(s);
    }else if(s.split("&")[0] == QObject::tr("1")){
        db->insertDoctorsData(s);
    }else if(s.split("&")[0] == QObject::tr("2")){
        QStringList update_data = s.split("&");
        db->updatePatient(update_data.at(1),update_data.at(2),update_data.at(3),update_data.at(4),update_data.at(5),
                              update_data.at(6),update_data.at(7),update_data.at(8),update_data.at(9),update_data.at(10));
    }

    emit update_view();
}

void ReceiveData::set_connection()
{
    connect(tcpsocket, SIGNAL(readyRead()),this,SLOT(readMessage()),Qt::DirectConnection);
}

void ReceiveData::set_arguments(QTcpSocket *tcpsocket, ServerDataBase *db)
{
    this->tcpsocket = tcpsocket;
    this->db = db;
}

void ReceiveData::readMessage()
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
        in >> blockSize;
        qDebug() << blockSize;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpsocket->bytesAvailable() < blockSize) return;
    // 将接收到的数据存放到变量中
    in >> message;
    // 显示接收到的数据
    qDebug() << message;

    //将数据写入mysql数据库
    insertInfor(message);
}

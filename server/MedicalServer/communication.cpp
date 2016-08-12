#include "communication.h"

Communication::Communication(int socketDescriptor, ServerDataBase *db, QObject *parent) :
    QThread(parent), socketDescriptor(socketDescriptor), db(db)
{
}

void Communication::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

//    connect(&tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(deal_state(QAbstractSocket::SocketState)));

    receiveData = new ReceiveData;
    receiveData->set_arguments(&tcpSocket,db);
    receiveData->set_connection();//连接

    connect(receiveData, SIGNAL(update_view()), this, SLOT(emit_update()));

    sendData = new SendData;
    sendData->set_arguments(&tcpSocket,db);

    //发送医生信息
    QString doctormessage("1");
    QStringList doctorstatements = db->selectDoctorsData();
    foreach (QString doctorstatement, doctorstatements) {
        doctormessage = doctormessage+"`"+doctorstatement;
    }
    qDebug() <<doctormessage;
    sendData->sendMessage(doctormessage);
    //发送患者信息
    QString patientmessage("0");
    QStringList patientstatements = db->selectPatientsData();
    foreach (QString patientstatement, patientstatements) {
        patientmessage = patientmessage+"`"+patientstatement;
    }
    sendData->sendMessage(patientmessage);

    exec();
}

void Communication::emit_update()
{
    emit update_view();
}

void Communication::deal_state(QAbstractSocket::SocketState state)
{
    if((state == QAbstractSocket::ClosingState)){
        qDebug("closing");
        disconnect();
        quit();
    }
}


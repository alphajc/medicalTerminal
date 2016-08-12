#ifndef SENDINFORMATION_H
#define SENDINFORMATION_H
#include <QString>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QtNetwork>
#include <QObject>

#include "communication.h"

class SendInformation: public QObject
{
    Q_OBJECT
public:
    SendInformation();
    ~SendInformation();
    void sendinformation(QString information);
private:
    QTcpSocket *tcpSocket;
    QString message;
    // 用来存放数据的大小信息
    quint16 blockSize;
};

#endif // SENDINFORMATION_H

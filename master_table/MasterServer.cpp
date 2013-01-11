#include <QtNetwork>
#include <QtCore>
#include "MasterServer.h"

MasterServer::MasterServer(bool mode, QObject *parent) :
    QObject(parent),autoMode(mode),counts(0)
{
    masterSocket = new QUdpSocket(this);
    masterSocket->bind(9500);
    connect(masterSocket, SIGNAL(readyRead()), this, SLOT(incomming()));
}

void
MasterServer::process(const QString &IPv4, QByteArray msg)
{
    QList<QByteArray> parts = msg.split(' ');
    emit updateBoardName("", IPv4, 0);
}

void
MasterServer::incomming()
{
    while (masterSocket->hasPendingDatagrams()) {
        QByteArray msg;
        msg.resize(masterSocket->pendingDatagramSize());
        QHostAddress sender;

        masterSocket->readDatagram(msg.data(),msg.size(), &sender);
        QString ip = sender.toString();
        process(ip, msg);
    }
}

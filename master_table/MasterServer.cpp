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
    if(parts.count() == 2) {
        QString cmd = parts.at(0);
        if(cmd == QString("needUi")) {
            quint16 thePort = parts.at(1).toUShort();
            if(autoMode) {
                counts++;
                emit updateBoardName("Default " + QString::number(counts), IPv4, thePort);
            } else {
                emit newBoardReady(IPv4, thePort);
            }
        }
    }

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

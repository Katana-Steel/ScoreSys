#include <QtNetwork>
#include <QtCore>
#include "error.h"
#include "testMasterServer.h"
#include "MasterServer.h"

// #include "udpCallback.h"

static void testRequestTitle();

void
testMasterServer(QTextStream &out)
{
    out << "entering MasterServer test" << endl;
    out << "Starting mock master server" << endl;
    MasterServer *master = new MasterServer();
    testRequestTitle();
    delete master;
}

static void
testRequestTitle()
{
    QUdpSocket *sock = new QUdpSocket();
    quint16 myPort = 25025;
    sock->bind(myPort);
    QByteArray datagram = "title " + QByteArray::number((uint)myPort);
    sock->writeDatagram(datagram,QHostAddress::Broadcast,9500);

}

#include <QtNetwork>
#include <QtCore>
#include "error.h"
#include "testMasterServer.h"
#include "testMasterServerObjects.h"
#include "MasterServer.h"

void
testMasterServer(QTextStream &out)
{
    new testMS(out);
}

testMS::testMS(QTextStream &_o)
    : QObject(),out(_o.device())
{
    out << "entering MasterServer test" << endl;
    out << "Starting mock master server" << endl;
    master = new MasterServer();


    // setting up the request title test
    out << "request Title from MasterServer" << endl;
    trqt = new testRequestTitle();
    connect(trqt,SIGNAL(finished(QObject*)),this, SLOT(destroyCases(QObject*)));
    connect(master,SIGNAL(updateBoardName(const QString&,const QString&,quint16)), trqt, SLOT(rqCallback(const QString&,const QString&, quint16)));
    trqt->start();
}

void
testMS::destroyCases(QObject *obj)
{
    if(obj == trqt) {
        delete trqt;
        trqt = 0;
        // last test case
        QCoreApplication::exit(0);
    }
}


testRequestTitle::testRequestTitle()
    : QObject(),myPort(25025)
{
}

void
testRequestTitle::start()
{
    QUdpSocket *sock = new QUdpSocket();
    sock->bind(myPort);
    QByteArray datagram = "needUi " + QByteArray::number((uint)myPort);
    sock->writeDatagram(datagram,QHostAddress::Broadcast,9500);
}

void
testRequestTitle::rqCallback(const QString &title, const QString&, quint16 port)
{
    if(port != myPort)
    {
        THROW_E("didn't get my port number back...");
    } else if(title.isEmpty()) {
        THROW_E("Got an empty title... wanted a little more");
    }
    emit finished(this);
}

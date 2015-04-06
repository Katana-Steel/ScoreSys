/* GPL preample */

#include <QtGui>
#include <QtNetwork>
#include "udp_ctl.h"
#include "sboard.h"

udpserver::udpserver(quint16 port, sboard *parent)
    : QObject(parent)
{
    my_port = port;
    timer = parent;
    sock = new QUdpSocket(this);
    sock->bind(port,QUdpSocket::DontShareAddress|QUdpSocket::ReuseAddressHint);

    connect(sock, SIGNAL(readyRead()), this, SLOT(udp_data()));
}

udpserver::~udpserver()
{
    delete sock;
}

void
udpserver::checkdata (QByteArray qba)
{
    if(qba.contains("tstop")) timer->stop_time();
    if(qba.contains("tstart")) timer->start_time();
    if(qba.contains("treset")) timer->reset_time();
    if(qba.contains("aka")) {
        int i = qba.indexOf("aka");
        i = qba.indexOf(" ", i);
        int j = qba.indexOf(" ", i+1);
        int p = qba.mid(i,j-i).toInt();
        timer->set_aka_points(p);
    }
    if(qba.contains("ao")) {
        int i = qba.indexOf("ao");
        i = qba.indexOf(" ", i);
        int j = qba.indexOf(" ", i+1);
        int p = qba.mid(i,j-i).toInt();
        timer->set_ao_points(p);
    }
    if(qba.contains("name")) {
        int i = qba.indexOf("name") + 4;
        int j = qba.indexOf(" ",i);
        QByteArray tmp = qba.mid(i,j-i);
        i = j+2;
        j = qba.indexOf("\"",i);
        if(tmp == QString("aka")) {
            timer->set_aka_name(qba.mid(i,j-i));
        }
        if(tmp == QString("ao")) {
            timer->set_ao_name(qba.mid(i,j-i));
        }
    }
    if(qba.contains("title")) {
        int i = qba.indexOf("title");
        i = qba.indexOf(" ") + 2;
        int j = qba.indexOf("\"",i);
        timer->set_title(qba.mid(i,j-i));
    }
    if(qba.contains("pen")) {
        int i = qba.indexOf("pen") + 3;
        int j = qba.indexOf(" ",i);
        QByteArray tmp = qba.mid(i,j-i);
        i = j+1;
        int cat;
        int pen;
        j = qba.indexOf(" ",i);
        cat = qba.mid(i,j-i).toInt();
        i = qba.indexOf(" ",j) + 1;
        j = 1;
        pen = qba.mid(i,j).toInt();
        if(tmp == QString("aka")) {
            timer->aka_penalty(cat,pen);
        }
        if(tmp == QString("ao")) {
            timer->ao_penalty(cat,pen);
        }
    }
}

void
udpserver::timerOps (QByteArray ops)
{}

void
udpserver::uiOps (QByteArray ops)
{}

void
udpserver::playerOps (QByteArray ops)
{}

void
udpserver::udp_data()
{
    while (sock->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(sock->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         sock->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

         checkdata(datagram);
     }
}

void
udpserver::requestTitle()
{
    QByteArray datagram = "needUi " + QByteArray::number((uint)my_port);
    sock->writeDatagram(datagram,QHostAddress::Broadcast,9500);
}

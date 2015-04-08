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
  QList<QByteArray> ops = qba.split(' ');
    if(qba.startsWith("timer ")) { 
      timerOps (ops);
    }
    if(qba.startsWith("SetUi ")) {
        uiOps (ops);
    }
    if(qba.startsWith("player ")) {
      int i = qba.indexOf(" ")+1;
      playerOps(qba.mid(i));
    }
}

void
udpserver::timerOps ( QList<QByteArray> ops)
{
  if (ops.count() > 2) {
    QList<QByteArray> t = ops.at(2).split(':');
    timer->reset_time(t.at(0).toInt(), t.at(1).toInt(), t.at(2).toInt());
  }
  if (ops.at(1) == "start")
    timer->start_time();
  if (ops.at(1) == "stop")
    timer->stop_time();

}

void
udpserver::uiOps ( QList<QByteArray> ops)
{
    if (ops.count()>=2) {
      ops.removeFirst();
      timer->set_title(ops.first().replace ('\'','');
      ops.removeFirst();
      if (!ops.isEmpty()) { 
        timer->set_score_ui(ops.first());
      }
    } 
}

void
udpserver::playerOps ( QByteArray ops)
{
  scoreBase *scores = timer->get_score_ui();
  if (scores == null)
    return;
  char pl = ops.at(0);
  QList<QByteArray> update();
  int i = ops.indexOf ("'")+1;
  int j = ops.indexOf ("'",i)-1;
  update.append (ops.mid (i,j-i));
  update.append (ops.mid (j+2).split (' '));
  if (pl == 'r')
    scores->setRightPlayer(update);
  if (pl == 'l')
    scores->setLeftPlayer(update);
}

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
         datagram.clear();
     }
}

void
udpserver::requestTitle()
{
    QByteArray datagram = "needUi " + QByteArray::number((uint)my_port);
    sock->writeDatagram(datagram,QHostAddress::Broadcast,9500);
}

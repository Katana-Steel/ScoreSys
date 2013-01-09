#include <QtNetwork>
#include <QtCore>
#include "error.h"
#include "testMasterServer.h"
#include "MasterServer.h"

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

}

/* GPL preample */

#include <QApplication>
#include "test.h"

int main(int ac, char** av)
{
    QApplication a(ac,av);
    try {
        test();
    }
    catch(...) {
        return -1;
    }
    return a.exec();
}

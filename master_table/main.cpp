/* GPL preample */

#include <QApplication>
#include "test.h"
#include "MasterUI.h"

int main(int ac, char** av)
{
    QApplication a(ac,av);
    try {
        test();
        if (! a.arguments().contains ("--test-only")) { 
            MainMasterUi *main = new MainMasterUi();
            main->show();
        }
    }
    catch(...) {
        return -1;
    }
    return 0;
}

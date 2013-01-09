/* GPL preamble */
#include <QtCore>
#include "test.h"
#include "error.h"

// next up one test header for each object
// all of which will throw an exception on failure
#include "testSQLdb.h"
#include "testMasterServer.h"

// the main test function
void test() {
	QTextStream out(stdout);
	out << "starting tests" << endl;
	try {
		testSQLdb(out);
        testMasterServer(out);
		out << "all tests passed!" << endl;
	}
	catch(Error *err) {
        out << err->filename << ":" << err->line << " --- "
            << endl << err->error << endl;
        throw err;
	}
}

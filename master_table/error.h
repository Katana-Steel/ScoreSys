/* GPL preamble */
#include <QString>

class Error {
public:
	long line;
	QString filename;
	QString error;
	Error(QString str){ this->error = str; };
};

#define THROW_E(s) Error *e = new Error(s); e->line = __LINE__; e->filename = __FILE__; throw e;


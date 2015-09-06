######################################################################
# Automatically generated by qmake (2.01a) Sat Jan 7 12:09:39 2012
######################################################################

TEMPLATE = app
TARGET = MasterServer
DEPENDPATH += .
INCLUDEPATH += . ./tests
QT += sql network

# Input
SOURCES += \
    main.cpp \
    SQLdb.cpp \
    MasterServer.cpp \
    MasterUI.cpp \
    tests/test.cpp \
    tests/testMasterServer.cpp \
    tests/testSQLdb.cpp

HEADERS += \
    error.h \
    SQLdb.h \
    MasterServer.h \
    MasterUI.h \
    tests/test.h \
    tests/testMasterServer.h \
    tests/testSQLdb.h \
    tests/testMasterServerObjects.h

FORMS += \
    MasterUI.ui

OTHER_FILES += \
    db_create.sql

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../common_lib/release/ -lcommon_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../common_lib/debug/ -lcommon_lib
else:symbian: LIBS += -lcommon_lib
else:unix: LIBS += -L$$PWD/../common_lib/ -lcommon_lib -Wl,-rpath ../common_lib/

INCLUDEPATH += $$PWD/../common_lib
DEPENDPATH += $$PWD/../common_lib

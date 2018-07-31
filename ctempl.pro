#-------------------------------------------------
#
# Project created by QtCreator 2018-07-31T16:37:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ctempl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QT_STRING_BUILDER

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainform.cpp

HEADERS += \
        mainform.h

FORMS += \
        mainform.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ctemplate-ctemplate-2.3/x64/Release/ -llibctemplate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ctemplate-ctemplate-2.3/x64/Debug/ -llibctemplate-debug

INCLUDEPATH += $$PWD/../ctemplate-ctemplate-2.3/src/windows/ctemplate
DEPENDPATH += $$PWD/../ctemplate-ctemplate-2.3/src/windows/ctemplate
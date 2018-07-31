/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief        类头/源文件。
 *
 * \version     0.1
 * \date        2018-7-31
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2018 Roy QIU。
 *
 **************************************************************************************************/
#include <QApplication>

#include "mainform.h"

#define QS(x)   QStringLiteral(x)


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName(QS("ctempl"));
    QApplication::setApplicationVersion(QS("0.1"));
    QApplication::setApplicationDisplayName(QS("Class template"));
    QApplication::setOrganizationName(QS("karoyqiu"));
    QApplication::setOrganizationDomain(QS("karoyqiu.gmail.com"));

    MainForm w;
    w.show();

    return a.exec();
}

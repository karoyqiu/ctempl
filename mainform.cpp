/*! ***********************************************************************************************
 *
 * \file        mainform.cpp
 * \brief       MainForm 类头/源文件。
 *
 * \version     0.1
 * \date        2018-7-31
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2018 Roy QIU。
 *
 **************************************************************************************************/
#include "mainform.h"
#include "ui_mainform.h"

#include <QStandardPaths>

#define QS(x)   QStringLiteral(x)


MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    loadTemplates();
}


MainForm::~MainForm()
{
    delete ui;
}


void MainForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainForm::loadTemplates()
{
    auto dir = QStandardPaths::locate(QStandardPaths::DataLocation, QS("templates"), QStandardPaths::LocateDirectory);
}

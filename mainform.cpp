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

#include <QClipboard>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSaveFile>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>

#include <ctemplate/template.h>

#define QS(x)   QStringLiteral(x)


static bool generateFile(const ctemplate::TemplateDictionary &dict, const QString &templateFilename,
                         const QString &targetFilename)
{
    std::string output;

    if (!ctemplate::ExpandTemplate(QDir::toNativeSeparators(templateFilename).toStdString(),
                                   ctemplate::DO_NOT_STRIP, &dict, &output))
    {
        return false;
    }

    QSaveFile file(targetFilename);

    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qCritical() << file.errorString();
        return false;
    }

    file.write(output.c_str(), output.length());
    return file.commit();
}


MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
    , templateDir_(QStandardPaths::locate(QStandardPaths::DataLocation, QS("templates"), QStandardPaths::LocateDirectory))
{
    ui->setupUi(this);
    connect(ui->buttonGenerate, &QPushButton::clicked, this, &MainForm::generate);

    loadSettings();
    loadTemplates();

    qDebug() << "Templates dir:" << templateDir_;
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


void MainForm::closeEvent(QCloseEvent *e)
{
    saveSettings();
    QWidget::closeEvent(e);
}


void MainForm::generate()
{
    QSettings settings;
    auto dir = settings.value(QS("dir")).toString();
    dir = QFileDialog::getExistingDirectory(this, {}, dir);

    if (dir.isEmpty())
    {
        return;
    }

    settings.setValue(QS("dir"), dir);

    ctemplate::TemplateDictionary dict("dict");
    dict.SetValue("CLASS", ui->editClass->text().toStdString());
    dict.SetValue("BASECLASS", ui->editBaseClass->text().toStdString());
    dict.SetValue("VERSION", ui->editVersion->text().toStdString());
    dict.SetValue("DATE", QDate::currentDate().toString(Qt::ISODate).toStdString());
    dict.SetValue("AUTHOR", ui->editAuthor->text().toStdString());
    dict.SetValue("EMAIL", ui->editEmail->text().toStdString());
    dict.SetValue("COPYRIGHT", ui->editCopyright->text().toStdString());

    QDir templateDir(templateDir_);
    templateDir.cd(ui->comboTemplate->currentText());

    for (const auto &s : templateDir.entryInfoList(QDir::Files))
    {
        QString filename = ui->editClass->text();

        if (s.baseName().contains(QLatin1Char('u')))
        {
            filename = filename.toLower();
        }

        qApp->clipboard()->setText(filename);
        dict.SetValue("FILENAME", filename.toStdString());
        filename = dir % "/" % filename % "." % s.completeSuffix();
        generateFile(dict, s.absoluteFilePath(), filename);
    }

    QMessageBox::information(this, {}, tr("Files are generated."));
}


void MainForm::loadSettings()
{
    QSettings settings;
    ui->editAuthor->setText(settings.value(QS("author")).toString());
    ui->editCopyright->setText(settings.value(QS("copyright")).toString());
    ui->editEmail->setText(settings.value(QS("email")).toString());
    ui->editVersion->setText(settings.value(QS("version")).toString());
}


void MainForm::saveSettings() const
{
    QSettings settings;
    settings.setValue(QS("author"), ui->editAuthor->text());
    settings.setValue(QS("copyright"), ui->editCopyright->text());
    settings.setValue(QS("email"), ui->editEmail->text());
    settings.setValue(QS("version"), ui->editVersion->text());
}


void MainForm::loadTemplates()
{
    if (templateDir_.isEmpty())
    {
        return;
    }

    QDir dir(templateDir_);
    ui->comboTemplate->addItems(dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::LocaleAware));
}

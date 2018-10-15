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

#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>

#include <ctemplate/template.h>

#define QS(x)   QStringLiteral(x)


class ToLowerModifier : public ctemplate::TemplateModifier
{
public:
    virtual void Modify(const char* in, size_t inlen,
                        const ctemplate::PerExpandData* per_expand_data,
                        ctemplate::ExpandEmitter* outbuf, const std::string &arg) const override
    {
        Q_UNUSED(per_expand_data);
        Q_UNUSED(arg);

        auto s = QString::fromUtf8(in, static_cast<int>(inlen));
        outbuf->Emit(s.toLower().toStdString());
    }
};


static bool generateFile(const ctemplate::TemplateDictionary &dict, const QString &templateFilename,
                         const QString &targetFilename)
{
    std::string output;

    if (!ctemplate::ExpandTemplate(QDir::toNativeSeparators(templateFilename).toStdString(),
                                   ctemplate::DO_NOT_STRIP, &dict, &output))
    {
        return false;
    }

    QFile file(targetFilename);

    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        return false;
    }

    file.write(output.c_str(), output.length());
    return true;
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

    ctemplate::AddModifier("x-to_lower", new ToLowerModifier);
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

    ctemplate::mutable_default_template_cache()->ReloadAllIfChanged(ctemplate::TemplateCache::LAZY_RELOAD);
    ctemplate::TemplateDictionary dict("dict");
    dict.SetValue("CLASS", ui->editClass->text().toStdString());
    dict.SetValue("BASECLASS", ui->editBaseClass->text().toStdString());
    dict.SetValue("VERSION", ui->editVersion->text().toStdString());
    dict.SetValue("DATE", QDate::currentDate().toString(Qt::ISODate).toStdString());
    dict.SetValue("AUTHOR", ui->editAuthor->text().toStdString());
    dict.SetValue("EMAIL", ui->editEmail->text().toStdString());
    dict.SetValue("COPYRIGHT", ui->editCopyright->text().toStdString());

    if (!ui->editNamespace->text().isEmpty())
    {
        auto *sub = dict.AddSectionDictionary("NAMESPACE");
        sub->SetValue("NAMESPACE", ui->editNamespace->text().toStdString());
    }

    QDir templateDir(templateDir_);
    templateDir.cd(ui->comboTemplate->currentText());

    for (const auto &s : templateDir.entryInfoList(QDir::Files))
    {
        QString filename = ui->editClass->text();

        if (s.baseName().contains(QLatin1Char('u')))
        {
            filename = filename.toLower();
        }

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
    ui->comboTemplate->setCurrentIndex(settings.value(QS("template")).toInt());
    ui->editBaseClass->setText(settings.value(QS("base")).toString());
    ui->editNamespace->setText(settings.value(QS("ns")).toString());
}


void MainForm::saveSettings() const
{
    QSettings settings;
    settings.setValue(QS("author"), ui->editAuthor->text());
    settings.setValue(QS("copyright"), ui->editCopyright->text());
    settings.setValue(QS("email"), ui->editEmail->text());
    settings.setValue(QS("version"), ui->editVersion->text());
    settings.setValue(QS("template"), ui->comboTemplate->currentIndex());
    settings.setValue(QS("base"), ui->editBaseClass->text());
    settings.setValue(QS("ns"), ui->editNamespace->text());
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

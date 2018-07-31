/*! ***********************************************************************************************
 *
 * \file        mainform.h
 * \brief       MainForm 类头/源文件。
 *
 * \version     0.1
 * \date        2018-7-31
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2018 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <QWidget>


namespace Ui {
class MainForm;
}


class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    virtual ~MainForm();

protected:
    virtual void changeEvent(QEvent *e) override;
    virtual void closeEvent(QCloseEvent *e) override;

private slots:
    void generate();

private:
    void loadSettings();
    void saveSettings() const;
    void loadTemplates();

private:
    Ui::MainForm *ui;
    QString templateDir_;
};

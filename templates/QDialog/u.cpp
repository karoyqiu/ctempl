/*! ***********************************************************************************************
 *
 * \file        {{FILENAME}}.cpp
 * \brief       {{CLASS}} 类源文件。
 *
 * \version     {{VERSION}}
 * \date        {{DATE}}
 *
 * \author      {{AUTHOR}} <{{EMAIL}}>
 * \copyright   {{COPYRIGHT}}
 *
 **************************************************************************************************/
#include "{{FILENAME}}.h"
#include "ui_{{FILENAME}}.h"


{{CLASS}}::{{CLASS}}(QWidget *parent /*= nullptr*/)
    : QDialog(parent)
    , ui(new Ui::{{CLASS}})
{
    ui->setupUi(this);
}


{{CLASS}}::~{{CLASS}}()
{
    delete ui;
}


void {{CLASS}}::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/*! ***********************************************************************************************
 *
 * \file        {{FILENAME}}.h
 * \brief       {{CLASS}} 类头文件。
 *
 * \version     {{VERSION}}
 * \date        {{DATE}}
 *
 * \author      {{AUTHOR}} <{{EMAIL}}>
 * \copyright   {{COPYRIGHT}}
 *
 **************************************************************************************************/
#pragma once
#include <QWidget>


namespace Ui {
class {{CLASS}};
}


class {{CLASS}} : public QWidget
{
    Q_OBJECT

public:
    explicit {{CLASS}}(QWidget *parent = nullptr);
    virtual ~{{CLASS}}();

protected:
    virtual void changeEvent(QEvent *e) override;

private:
    Ui::{{CLASS}} *ui;
};

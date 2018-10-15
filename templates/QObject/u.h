/*! ***********************************************************************************************
 *
 * \file        {{CLASS:x-to_lower}}.h
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
#include <{{BASECLASS}}>
#include "{{BASECLASS:x-to_lower}}.h"

{{#NAMESPACE}}{{BI_NEWLINE}}namespace {{NAMESPACE}} {{{BI_NEWLINE}}{{BI_NEWLINE}}{{/NAMESPACE}}
class {{CLASS}} : public {{BASECLASS}}
{
    Q_OBJECT

public:
    explicit {{CLASS}}(QObject *parent = nullptr);
};
{{#NAMESPACE}}{{BI_NEWLINE}}{{BI_NEWLINE}}}       // namespace {{NAMESPACE}}{{/NAMESPACE}}

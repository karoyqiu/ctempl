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


{{CLASS}}::{{CLASS}}(QObject *parent)
    : QAbstractTableModel(parent)
{
}


QVariant {{CLASS}}::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant var;

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        default:
            break;
        }
    }

    return var;
}


int {{CLASS}}::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    // FIXME: Implement me!
}


int {{CLASS}}::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return ColumnCount;
}


QVariant {{CLASS}}::data(const QModelIndex &idx, int role) const
{
    Q_ASSERT(checkIndex(idx, CheckIndexOption::IndexIsValid | CheckIndexOption::ParentIsInvalid));

    QVariant var;

    if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::ToolTipRole)
    {
    }

    return var;
}

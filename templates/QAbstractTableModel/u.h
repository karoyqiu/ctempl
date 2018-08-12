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
#include <QAbstractTableModel>


class {{CLASS}} : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column
    {
        ColumnCount
    };

    explicit {{CLASS}}(QObject *parent = nullptr);

    // Header:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = {}) const override;
    virtual int columnCount(const QModelIndex &parent = {}) const override;

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;

private:
};

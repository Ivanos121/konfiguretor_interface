#ifndef MODEL_H
#define MODEL_H

#include "QSqlDatabase"
#include <QSqlError>
#include "QtSql"

class Model : public QSqlTableModel
{
public:
    Model();
    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    QVariant data2 ( const QModelIndex & index, int role = Qt::DisplayRole );
    void onChecked(int index, int orientation);
    void getColorForRow(const QModelIndex &row);

signals:
    //void dataChanged(const QModelIndex &, const QModelIndex &, const QVector <int> &);

};
#endif // MODEL_H

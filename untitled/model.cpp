#include "model.h"

Model::Model()
{

}

Qt::ItemFlags  Model::flags(const QModelIndex & index) const{
  // Column 0 always records the mark variable (our boolean).
  if (index.column() == 1 || index.column() == 2) {
    // Make sure that this item is checkable.
    return QSqlTableModel::flags(index) | Qt::ItemIsUserCheckable;
  }
  // Default behaviour in all other cases.
  return QSqlTableModel::flags(index);
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (index.column() == 1 || index.column() == 2)
    {
        if (role == Qt::CheckStateRole)
        {
            int checked = QSqlTableModel::data(index).toInt();

            if (checked)
            {
                return Qt::Checked;
            }
            else
            {
                return Qt::Unchecked;
            }
        }
        else
        {
            return QSqlTableModel::data(index, role);
        }
    }
    else if(role == Qt::TextAlignmentRole)
    {
        if (index.column() >= 4)
            return int(Qt::AlignCenter);
    }

    return QSqlTableModel::data(index, role);
 }

bool Model::setData(const QModelIndex & index, const QVariant & value, int role)
{

  /*
     Let's check whether the selected column is the column with our boolean variable
     (always column 7), and whether we are trying to set data under the
     Qt::CheckStateRole.
  */
  if ((index.column() == 1 && role == Qt::CheckStateRole) || (index.column() == 2 && role == Qt::CheckStateRole))
    {
      // Writing the data when the check box is set to checked.
      if (value == Qt::Checked)
    {
      // Let's write the new value
      return setData(index, 1);
      // Writing the data when the check box is set to unchecked
    }
      else if (value == Qt::Unchecked)
    {
      // Let's write the new value
      return setData(index, 0);
    }
    }
    // In all other situations revert to default behaviour.
  return QSqlTableModel::setData(index, value, role);
}

void Model::onChecked(int index, int orientation)
{
    int m_row=16;
    int m_column=64;
    if (orientation == Qt::Horizontal)
        emit dataChanged(createIndex(0, index), createIndex(m_row - 1, index), { Qt::DisplayRole });
    else
        emit dataChanged(createIndex(index, 0), createIndex(index, m_column - 1), { Qt::DisplayRole });
}





#include "searchlogmodel.h"
#include <QDebug>

SearchLogModel::SearchLogModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void SearchLogModel::onRegularExpressionEnabled(bool enabled)
{

}

void SearchLogModel::onSearchButtonClicked(const QString searchString)
{
    qDebug() << "re: " << searchString;
    setFilterRegExp(searchString);
}

bool SearchLogModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (filterRegExp().isEmpty())
        return false;
    QModelIndex index = sourceModel()->index(sourceRow, 3, sourceParent);
    return (sourceModel()->data(index).toString().contains(filterRegExp()));
}

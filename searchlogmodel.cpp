#include "searchlogmodel.h"
#include <QRegExp>
#include <QDebug>

SearchLogModel::SearchLogModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void SearchLogModel::onRegularExpressionEnabled(bool enabled)
{
    m_isReEnabled = enabled;
}

void SearchLogModel::onSearchButtonClicked(const QString searchString)
{
    Qt::CaseSensitivity cs = m_isCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (m_isReEnabled && !searchString.isEmpty()) {
        QRegExp regExp(searchString, cs);
        setFilterRegExp(regExp);
    } else if (searchString.isEmpty()) {
        QRegExp regExp(QString("*"), cs, QRegExp::Wildcard);
        setFilterRegExp(regExp);
    } else {
        QRegExp regExp(searchString, cs, QRegExp::Wildcard);
        setFilterRegExp(regExp);
    }
}

void SearchLogModel::onCaseSensitiveClicked(bool isCaseSensitive)
{
    m_isCaseSensitive = isCaseSensitive;
}

bool SearchLogModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 6, sourceParent);
    return (sourceModel()->data(index).toString().contains(filterRegExp()));
}

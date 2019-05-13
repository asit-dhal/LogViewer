#ifndef SEARCHLOGMODEL_H
#define SEARCHLOGMODEL_H

#include <QSortFilterProxyModel>

class SearchLogModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SearchLogModel(QObject *parent = nullptr);
    void onRegularExpressionEnabled(bool enabled);
    void onSearchButtonClicked(const QString searchString);
    void onCaseSensitiveClicked(bool isCaseSensitive);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool m_isReEnabled = false;
    bool m_isCaseSensitive = false;
};

#endif // SEARCHLOGMODEL_H

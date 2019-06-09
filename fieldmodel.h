#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QAbstractTableModel>
#include "field.h"

class FieldModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum { eName = 0, eType };
    explicit FieldModel(QObject *parent = nullptr);

    static FieldModel *instance();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;

    void addField(const Field &field, int index = -1);
    void removeField(int index);

private:
    static FieldModel *m_instance;
};



#endif // FIELDMODEL_H

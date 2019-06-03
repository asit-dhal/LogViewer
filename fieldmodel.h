#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QAbstractTableModel>

enum class FieldType {
    eString = 0,
    eNumber,
    eTimestamp
};

const QString fieldTypeToString(FieldType fieldType);
FieldType stringToFieldType(const QString& fieldType);

struct Field {
    QString name;
    unsigned int index;
    FieldType fieldType;
    Field();
    Field(QString name, unsigned int index, FieldType fieldType);
};

class FieldModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum { eIndex = 0, eName, eType };
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
    void correctIndexes();

    static FieldModel *m_instance;
    QList<Field> m_fields;

};



#endif // FIELDMODEL_H

#include "fieldmodel.h"
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <QApplication>

const QString fieldTypeToString(FieldType fieldType)
{
    switch (fieldType) {
        case FieldType::eString: return QString("Name");
        case FieldType::eNumber: return QString("Number");
        case FieldType::eTimestamp: return QString("Timestamp");
    }
}

FieldType stringToFieldType(const QString& fieldType)
{
    if (QString::compare(fieldType, "name", Qt::CaseInsensitive) == 0)
        return FieldType::eString;
    else if (QString::compare(fieldType, "number", Qt::CaseInsensitive) == 0)
        return FieldType::eNumber;
    else
        return  FieldType::eTimestamp;
}

Field::Field()
{
    name = QObject::tr("Default");
    index = static_cast<unsigned int>(FieldModel::instance()->rowCount() + 1);
    fieldType = FieldType::eString;
}

Field::Field(QString name, unsigned int index, FieldType fieldType) :
    name(name), index(index), fieldType(fieldType)
{
}


FieldModel *FieldModel::m_instance = nullptr;

FieldModel::FieldModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_instance = this;
}

FieldModel *FieldModel::instance()
{
    return m_instance;
}

QVariant FieldModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return tr("Index");
            case 1: return tr("Name");
            case 2: return tr("Type");
            default:
                return QVariant();
            }
        }
    }

    return QVariant();
}

int FieldModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_fields.size();
}

int FieldModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 3;
}

Qt::ItemFlags FieldModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        flags |= Qt::ItemIsSelectable|Qt::ItemIsEditable|
                    Qt::ItemIsEnabled;
    }
    return flags;
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_fields.count() ||
            index.column() < 0 || index.row() >= 3) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case eIndex: return m_fields.at(index.row()).index;
            case eName: return m_fields.at(index.row()).name;
            case eType: return fieldTypeToString(m_fields.at(index.row()).fieldType);
            default: Q_ASSERT(false);
        }
    }

    if (role == Qt::SizeHintRole) {
        QStyleOptionComboBox option;
        const Field currentField = m_fields.at(index.row());
        switch (index.column()) {
        case eIndex:
        {
            option.currentText = QString::number(m_fields.at(m_fields.count()-1).index);
            const QString header = headerData(eIndex, Qt::Horizontal, Qt::DisplayRole).toString();
            if (header.length() > option.currentText.length())
                option.currentText = header;
            break;
        }
        case eName:
        {
            option.currentText = currentField.name;
            break;
        }
        case eType:
        {
            option.currentText = fieldTypeToString(m_fields.at(index.row()).fieldType);
            break;
        }
        default:
        {
            Q_ASSERT(false);
        }
        }
        QFontMetrics fontMetrics(data(index, Qt::FontRole).value<QFont>());
        option.fontMetrics = fontMetrics;
        QSize size(fontMetrics.width(option.currentText), fontMetrics.height());
        return qApp->style()->sizeFromContents(QStyle::CT_ComboBox, &option, size);
    }
    return QVariant();
}

void FieldModel::addField(const Field &field, int index)
{
    if (index >= 0) {
        beginInsertRows(QModelIndex(), index, index);
    } else {
        beginInsertRows(QModelIndex(), m_fields.size(), m_fields.size());
    }
    m_fields.append(field);
    endInsertRows();
}

void FieldModel::removeField(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_fields.removeAt(index);
    endRemoveRows();

    correctIndexes();
}

bool FieldModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole ||
        index.row() < 0 || index.row() >= m_fields.count() ||
        index.column() < 0 || index.column() >= 3)
        return false;
    Field &field = m_fields[index.row()];
    switch (index.column()) {
        case eIndex:
            return false;
        case eName:
            field.name = value.toString();
            break;
        case eType:
            field.fieldType = stringToFieldType(value.toString());
            break;
        default: Q_ASSERT(false);
    }
    emit dataChanged(index, index);
    return true;
}

void FieldModel::correctIndexes()
{
    beginResetModel();

    for (int i=0; i<m_fields.size(); i++) {
        m_fields[i].index = static_cast<unsigned int>(i+1);
    }

    endResetModel();
}

#include "fieldmodel.h"
#include "project.h"
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <QApplication>


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
            case 0: return tr("Name");
            case 1: return tr("Type");
            default:
                return QVariant();
            }
        } else {
            return QString::number(section);
        }
    }
    return QVariant();
}

int FieldModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Project::instance()->fieldCount();
}

int FieldModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 2;
}

Qt::ItemFlags FieldModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        flags |= Qt::ItemIsSelectable | Qt::ItemIsEditable |
                    Qt::ItemIsEnabled;
    }
    return flags;
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    auto project = Project::instance();

    if (!index.isValid() || index.row() < 0 || index.row() >= project->fieldCount() ||
            index.column() < 0 || index.column() >= 3) {
        return QVariant();
    }

    const Field currentField = project->fieldAt(index.row());
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case eName: return currentField.name;
            case eType: return fieldTypeToString(currentField.fieldType);
            default: Q_ASSERT(false);
        }
    }

    if (role == Qt::SizeHintRole) {
        QStyleOptionComboBox option;
        switch (index.column()) {
        case eName:
            option.currentText = currentField.name;
            break;
        case eType:
            option.currentText = fieldTypeToString(currentField.fieldType);
            break;
        default:
            Q_ASSERT(false);
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
        beginInsertRows(QModelIndex(), Project::instance()->fieldCount(), Project::instance()->fieldCount());
    }
    Project::instance()->addField(field);
    endInsertRows();
}

void FieldModel::removeField(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    Project::instance()->removeFieldAt(index);
    endRemoveRows();
}

bool FieldModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto project = Project::instance();

    if (!index.isValid() || role != Qt::EditRole ||
        index.row() < 0 || index.row() >= project->fieldCount() ||
        index.column() < 0 || index.column() >= 3)
        return false;
    Field &field = project->fieldAt(index.row());
    switch (index.column()) {
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

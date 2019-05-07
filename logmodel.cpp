#include "logmodel.h"

LogModel::LogModel(QObject* parent) : QAbstractTableModel(parent)
{
}

void LogModel::addLogRecord(const LogRecord &record)
{
    beginInsertRows(QModelIndex(), m_records.size(), m_records.size());
    m_records.append(record);
    endInsertRows();
}

void LogModel::bulkAddLogRecords(const QList<LogRecord> &records)
{
    beginInsertRows(QModelIndex(), m_records.size(), m_records.size()+records.size()-1);
    m_records << records;
    endInsertRows();
}

void LogModel::clear()
{
    beginResetModel();
    m_records.clear();
    endResetModel();
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case FieldName::eTimestamp: return tr("Timestamp");
            case FieldName::eThreadId: return tr("Thread Id");
            case FieldName::eLogLevel: return tr("Log Level");
            case FieldName::eCategory: return tr("Category");
            case FieldName::eFileName: return tr("Filename");
            case FieldName::eLineNumber: return tr("Line Number");
            case FieldName::eMessage: return tr("Payload");
            default:
                return QVariant();
            }
        }

        if (orientation == Qt::Vertical) {
            return QString("%1").arg(section + 1);
        }
    }

    if (role == Qt::TextAlignmentRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case FieldName::eTimestamp: return QVariant(Qt::AlignCenter | Qt::AlignVCenter);;
                case FieldName::eThreadId:  return QVariant(Qt::AlignCenter | Qt::AlignVCenter);;
                case FieldName::eLogLevel:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
                case FieldName::eCategory:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
                case FieldName::eFileName:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
                case FieldName::eLineNumber: return QVariant(Qt::AlignRight | Qt::AlignVCenter);;
                case FieldName::eMessage:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
                default: return QVariant();
            }
        }

        return QVariant();
    }

    return QVariant();
}

int LogModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_records.size();
}

int LogModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 7;
}

QVariant LogModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_records.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case FieldName::eTimestamp: return m_records[index.row()].timestamp;
            case FieldName::eThreadId: return m_records[index.row()].threadId;
            case FieldName::eLogLevel: return m_records[index.row()].logLevel;
            case FieldName::eCategory: return m_records[index.row()].category;
            case FieldName::eFileName: return m_records[index.row()].filename;
            case FieldName::eLineNumber: return m_records[index.row()].lineNumber;
            case FieldName::eMessage: return m_records[index.row()].message;
			default: return QVariant();
        }
    }

    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
            case FieldName::eTimestamp: return QVariant(Qt::AlignCenter | Qt::AlignVCenter);;
            case FieldName::eThreadId:  return QVariant(Qt::AlignCenter | Qt::AlignVCenter);;
            case FieldName::eLogLevel:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
            case FieldName::eCategory:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
            case FieldName::eFileName:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
            case FieldName::eLineNumber: return QVariant(Qt::AlignRight | Qt::AlignVCenter);;
            case FieldName::eMessage:  return QVariant(Qt::AlignLeft | Qt::AlignVCenter);;
            default: return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags LogModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}


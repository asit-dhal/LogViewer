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
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QString("Timestamp");
		case 1: return QString("Thread Id");
        case 2: return QString("Log Level");
        case 3: return QString("Payload");
        default:
            return QVariant();
        }
    }

    if (orientation == Qt::Vertical) {
        return QString("%1").arg(section + 1);
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
    return 4;
}

QVariant LogModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_records.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return m_records[index.row()].timestamp;
			case 1: return m_records[index.row()].threadId;
            case 2: return m_records[index.row()].logLevel;
            case 3: return m_records[index.row()].message;
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


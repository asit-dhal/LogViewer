#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>
#include <QList>

struct LogRecord
{
    QDateTime timestamp;
	QString threadId;
    QString logLevel;
    QString message;
};

class LogModel : public QAbstractTableModel
{
 Q_OBJECT
public:
    explicit LogModel(QObject* parent = nullptr);
    void addLogRecord(const LogRecord &record);
    void bulkAddLogRecords(const QList<LogRecord> &records);
    void clear();
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QList<LogRecord> m_records;
};


#endif // LOGMODEL_H

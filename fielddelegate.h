#ifndef FIELDDELEGATE_H
#define FIELDDELEGATE_H

#include <QStyledItemDelegate>


class QModelIndex;
class QPainter;
class QStyleOptionViewItem;

class FieldDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FieldDelegate(QObject *parent=0)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // FIELDDELEGATE_H

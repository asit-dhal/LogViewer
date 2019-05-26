#include "fielddelegate.h"
#include "fieldmodel.h"
#include <QComboBox>
#include <QLineEdit>
#include <QModelIndex>
#include <QPainter>

void FieldDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == FieldModel::eIndex) {
        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);
        QString text = QString("%1").arg(opt.text.toInt(), 5, 10, QChar('0'));
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        if (opt.state & QStyle::State_Selected) {
            painter->fillRect(opt.rect, opt.palette.highlight());
            painter->setPen(opt.palette.highlightedText().color());
        }
        else {
            painter->setPen(opt.palette.windowText().color());
        }

        painter->drawText(opt.rect.adjusted(0, 0, -3, 0), text,
                QTextOption(Qt::AlignVCenter|Qt::AlignRight));
        painter->restore();
    }
    else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *FieldDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static QStringList fieldTypes;
    if (fieldTypes.isEmpty()) {
        fieldTypes << fieldTypeToString(FieldType::eNumber)
                   << fieldTypeToString(FieldType::eString)
                   << fieldTypeToString(FieldType::eTimestamp);
    }

    if (index.column() == FieldModel::eName) {
        return new QLineEdit(parent);
    }
    if (index.column() == FieldModel::eType) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(fieldTypes);
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);

}

void FieldDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == FieldModel::eName) {
        QString name = index.model()->data(index).toString();
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(lineEdit);
        lineEdit->setText(name);
    } else if (index.column() == FieldModel::eType) {
        FieldType fieldType = stringToFieldType(index.model()->data(index).toString());
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(comboBox);
        comboBox->setCurrentIndex(comboBox->findText(fieldTypeToString(fieldType)));
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void FieldDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == FieldModel::eName) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(lineEdit);
        model->setData(index, lineEdit->text().trimmed());
    } else if (index.column() == FieldModel::eType) {
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(comboBox);
        model->setData(index, comboBox->currentText());
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

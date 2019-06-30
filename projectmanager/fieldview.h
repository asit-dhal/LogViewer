#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QTableView>

namespace ProjectManager {

class QAbstractItemModel;

class FieldView : public QTableView
{
    Q_OBJECT
public:
    explicit FieldView(QWidget *parent=nullptr);
    virtual ~FieldView() = default;

 private slots:
    void onContextMenuOnHeader(QPoint p);
    void onContextMenuOnBody(QPoint p);
    void onSlotMoveLast();
    void onSlotMoveFirst();
};

} // ProjectManager

#endif // FIELDVIEW_H

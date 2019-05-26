#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QTableView>

class QAbstractItemModel;

class FieldView : public QTableView
{
public:
    FieldView(QAbstractItemModel * model);
};

#endif // FIELDVIEW_H

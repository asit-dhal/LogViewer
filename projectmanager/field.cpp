#include "field.h"
#include "fieldmodel.h"
#include <QObject>

namespace ProjectManager {

const QString fieldTypeToString(FieldType fieldType)
{
    switch (fieldType) {
        case FieldType::eString: return QString("String");
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
    fieldType = FieldType::eString;
}

Field::Field(QString name, FieldType fieldType) :
    name(name), fieldType(fieldType)
{
}

bool Field::operator==(const Field &field) const
{
    return QString::compare( name, field.name, Qt::CaseInsensitive);
}

} // ProjectManager

#ifndef FIELD_H
#define FIELD_H

#include <QString>

namespace ProjectManager {

enum class FieldType {
    eString = 0,
    eNumber,
    eTimestamp
};

const QString fieldTypeToString(FieldType fieldType);
FieldType stringToFieldType(const QString& fieldType);

struct Field {
    QString name;
    FieldType fieldType;
    Field();
    Field(QString name, FieldType fieldType);
    bool operator==(const Field &field) const;
};

} // ProjectManager

#endif // FIELD_H

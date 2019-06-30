#include "project.h"

namespace ProjectManager {


Project *Project::m_instance = nullptr;

Project::Project(QObject *parent) : QObject(parent)
{
    m_instance = this;
}

QString Project::name() const
{
    return m_name;
}

void Project::setName(const QString &name)
{
    m_name = name;
}

QString Project::path() const
{
    return m_path;
}

void Project::setPath(const QString &path)
{
    m_path = path;
}

Project *Project::instance()
{
    return m_instance;
}

QHostAddress Project::ipAddress() const
{
    return m_ipAddress;
}

unsigned int Project::portNumber() const
{
    return m_portNumber;
}

void Project::clear()
{
    m_name.clear();
    m_path.clear();
    m_fields.clear();
}

void Project::addField(const Field &field)
{
    m_fields.append(field);
}

void Project::addField(const QString &name, FieldType fieldType)
{
    m_fields.append(Field(name, fieldType));
    emit fieldChanged();
}

const Field &Project::fieldAt(int index) const
{
    return m_fields[index];
}

Field &Project::fieldAt(int index)
{
    return m_fields[index];
}

void Project::removeField(const QString &name)
{
    Field field(name, FieldType::eNumber);
    m_fields.removeOne(field);
}

void Project::removeFieldAt(int index)
{
    m_fields.removeAt(index);
}

int Project::fieldCount() const
{
    return m_fields.size();
}

void Project::setIpAddress(const QHostAddress &ipAddress)
{
    m_ipAddress = ipAddress;
}

void Project::setPortNumber(unsigned int portNumber)
{
    m_portNumber = portNumber;
}

} // ProjectManager

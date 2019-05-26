#include "project.h"

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

void Project::clear()
{
    m_name.clear();
    m_path.clear();
    m_fields.clear();
}

void Project::addField(unsigned int index, QString name, FieldType fieldType)
{
    m_fields[index] = Field(name, index, fieldType);
    emit fieldChanged();
}

Project::Field Project::fieldAt(unsigned int index) const
{
    return m_fields.value(index);
}

int Project::fieldCount() const
{
    return m_fields.size();
}


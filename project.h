#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QMap>
#include <QHostAddress>
#include "field.h"

class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    void addField(const Field &field);
    void addField(const QString &name, FieldType fieldType);
    void removeField(const QString &name);
    void removeFieldAt(int index);
    const Field &fieldAt(int index) const;
    Field &fieldAt(int index);
    int fieldCount() const;

    void clear();
    void setIpAddress(const QHostAddress &ipAddress);
    void setPortNumber(unsigned int portNumber);

    static Project *instance();

    QHostAddress ipAddress() const;
    unsigned int portNumber() const;

signals:
    void portChanged(unsigned int port);
    void ipAddressChanged(QHostAddress ipAddress);
    void fieldChanged();

public slots:

private:
    QString m_name;
    QString m_path;
    QList<Field> m_fields;
    QHostAddress m_ipAddress = QHostAddress::Null;
    unsigned int m_portNumber = 0;
    static Project *m_instance;

};

#endif // PROJECT_H

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QHostAddress>

class Configuration : public QObject
{
    Q_OBJECT
public:
    enum class FieldType {
        eString,
        eInt,
        eTimestamp
    };

    struct Field {
        QString name;
        unsigned int index;
        FieldType fieldType;

        Field(){}

        Field(QString name, unsigned int index, FieldType fieldType) :
            name(name), index(index), fieldType(fieldType)
        {
        }
    };

    explicit Configuration(QObject *parent = nullptr);
    static Configuration* getInstance();


    unsigned int port() const;
    void setPort(unsigned int port);

    QHostAddress ipAddress() const;
    void setIpAddress(const QHostAddress &ipAddress);

    void clearAllFields();
    void addField(unsigned int index, QString name, FieldType fieldType);
    Field fieldAt(unsigned int index) const;
    int fieldCount() const;

    void load(const QString &filename);



signals:
    void portChanged(unsigned int port);
    void ipAddressChanged(QHostAddress ipAddress);
    void fieldChanged();

public slots:

private:
    unsigned int m_port;
    QHostAddress m_ipAddress;
    static Configuration *m_configuration;
    QMap<unsigned int, Field> m_fields;
};

#endif // CONFIGURATION_H

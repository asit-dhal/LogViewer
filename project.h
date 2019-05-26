#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QMap>
#include <QHostAddress>

class Project : public QObject
{
    Q_OBJECT
public:
    enum class FieldType {
        eString,
        eNumber,
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

    explicit Project(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    void addField(unsigned int index, QString name, FieldType fieldType);
    Field fieldAt(unsigned int index) const;
    int fieldCount() const;

    void clear();

    static Project *instance();

signals:
    void portChanged(unsigned int port);
    void ipAddressChanged(QHostAddress ipAddress);
    void fieldChanged();

public slots:

private:
    QString m_name;
    QString m_path;
    QMap<unsigned int, Field> m_fields;

    static Project *m_instance;

};

#endif // PROJECT_H

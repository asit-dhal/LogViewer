#include "configuration.h"
#include "settingsdialog.h"

#include <QtXml>
#include <QFile>
#include <QMessageBox>

Configuration::Configuration(QObject *parent) : QObject(parent)
{
}

unsigned int Configuration::port() const
{
    return m_port;
}

void Configuration::setPort(unsigned int port)
{
    m_port = port;
    emit portChanged(port);
}

QHostAddress Configuration::ipAddress() const
{
    return m_ipAddress;
}

void Configuration::setIpAddress(const QHostAddress &ipAddress)
{
    m_ipAddress = ipAddress;
    emit ipAddressChanged(m_ipAddress);
}

void Configuration::clearAllFields()
{
    m_fields.clear();
    emit fieldChanged();
}

void Configuration::addField(unsigned int index, QString name, FieldType fieldType)
{
    m_fields[index] = Field(name, index, fieldType);
    emit fieldChanged();
}

Configuration::Field Configuration::fieldAt(unsigned int index) const
{
    return m_fields.value(index);
}

int Configuration::fieldCount() const
{
    return m_fields.size();
}

void Configuration::load(const QString &filename)
{
    QFile *xmlFile = new QFile(filename);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        SettingsDialog::getSettingsDialog()->updateStatus(QString("%1 is not a readonly text file").arg(filename));
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(xmlFile)) {
        SettingsDialog::getSettingsDialog()->updateStatus(QString("%1 is not a valid xml file").arg(filename));
        return;
    }

    QDomNodeList application = doc.elementsByTagName("application");
    if (application.isEmpty()) {
        SettingsDialog::getSettingsDialog()->updateStatus(QString("%1 does not contain an application tag").arg(filename));
        return;
    }
    QDomNodeList globalConfig = doc.elementsByTagName("global-config");
    if (!globalConfig.isEmpty()) {
        QDomNode n = globalConfig.item(0);
        QDomElement port = n.firstChildElement("port");
        QDomElement ipAddress = n.firstChildElement("hostname");

        qDebug() << "port: " << port.text() << " address: " << ipAddress.text();
        if (!port.isNull())
            setPort(port.text().toUInt());
        else
            setPort(28000);

        if (!ipAddress.isNull()) {
            if (ipAddress.text() == "broadcast")
                setIpAddress(QHostAddress::Broadcast);
            else if (ipAddress.text() == "localhost")
                setIpAddress(QHostAddress::LocalHost);
            else
                setIpAddress(QHostAddress(ipAddress.text()));
        } else {
            setIpAddress(QHostAddress::Broadcast);
        }

    }

    QDomNodeList logFormat = doc.elementsByTagName("field");

    blockSignals(true);
    if (!logFormat.isEmpty()) {
        for (int i=0; i<logFormat.size(); i++) {
            QDomNode n = logFormat.item(i);
            QDomNamedNodeMap attrs = n.attributes();
            unsigned int index  = 0;
            if (!attrs.namedItem("index").isNull())
                index = attrs.namedItem("index").nodeValue().toUInt();

            QDomElement nameElement = n.firstChildElement("name");
            QDomElement typeElement = n.firstChildElement("type");

            QString name;
            if (!nameElement.isNull())
                name = nameElement.text();
            FieldType fieldType = FieldType::eString;
            if (!typeElement.isNull()) {
                if (typeElement.text() == "Datetime")
                    fieldType = FieldType::eTimestamp;
                else if (typeElement.text() == "Integer")
                    fieldType = FieldType::eInt;
                else
                    fieldType = FieldType::eString;
            }

            addField(index, name, fieldType);
        }
    }
    blockSignals(false);
    emit fieldChanged();

    xmlFile->close();
}

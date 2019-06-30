#include "helper/appconfig.h"

namespace Helper {

void AppConfig::loadAppSettings()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
}

QString AppConfig::getDefaultProjectLocation()
{
    QSettings appSettings;
    appSettings.beginGroup("default-location");
    QString path = appSettings.value("path").toString();
    appSettings.endGroup();
    return path;
}

void AppConfig::updateDefaultProjectLocation(const QString &location)
{
    QSettings appSettings;
    appSettings.beginGroup("default-location");
    appSettings.setValue("path", location);
    appSettings.endGroup();
}

} // namespace helper

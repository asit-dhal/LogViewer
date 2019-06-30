#pragma once

#include <QSettings>
#include <QStringList>

namespace Helper {

class AppConfig
{
public:
    static void loadAppSettings();
    static QString getDefaultProjectLocation();
    static void updateDefaultProjectLocation(const QString &location);
};

} // namespace helper

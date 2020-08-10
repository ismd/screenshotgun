#include "AutoStartup.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>

void AutoStartup::set(const bool enabled) {
#if defined(Q_OS_LINUX)
    setLinux(enabled);
#elif defined(Q_OS_WIN32)
    setWindows(enabled);
#endif
}

#if defined(Q_OS_LINUX)
void AutoStartup::setLinux(const bool enabled) {
    QString autoStartPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
        + QLatin1String("/autostart/");

    QString desktopFileLocation = autoStartPath
        + "Screenshotgun"
        + QLatin1String(".desktop");

    if (enabled) {
        if (!QDir().exists(autoStartPath) && !QDir().mkpath(autoStartPath)) {
            qInfo() << "Can't create autostart directory";
            return;
        }

        QFile iniFile(desktopFileLocation);
        if (!iniFile.open(QIODevice::WriteOnly)) {
            qInfo() << "Can't write autostart entry" << desktopFileLocation;
            return;
        }

        QTextStream ts(&iniFile);
        ts.setCodec("UTF-8");
        ts << QLatin1String("[Desktop Entry]") << '\n'
           << QLatin1String("Name=") << "Screenshotgun" << '\n'
//           << QLatin1String("GenericName=") << QLatin1String("File Synchronizer") << '\n'
           << QLatin1String("Exec=") << QCoreApplication::applicationFilePath() << '\n'
           << QLatin1String("Terminal=") << "false" << '\n'
//           << QLatin1String("Icon=") << appName.toLower() << '\n' // always use lowercase for icons
           << QLatin1String("Categories=") << QLatin1String("Network") << '\n'
           << QLatin1String("Type=") << QLatin1String("Application") << '\n'
           << QLatin1String("StartupNotify=") << "false" << '\n'
           << QLatin1String("X-GNOME-Autostart-enabled=") << "true" << '\n';
    } else {
        if (QFile(desktopFileLocation).exists() && !QFile::remove(desktopFileLocation)) {
            qInfo() << "Can't remove autostart desktop file";
        }
    }
}
#endif

#if defined(Q_OS_WIN32)
void AutoStartup::setWindows(const bool enabled) {
    QString runPath = QLatin1String("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    QSettings settings(runPath, QSettings::NativeFormat);

    if (enabled) {
        settings.setValue("Screenshotgun", QCoreApplication::applicationFilePath().replace('/','\\'));
    } else {
        settings.remove("Screenshotgun");
    }
}
#endif

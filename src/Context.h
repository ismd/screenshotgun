#pragma once

#include "utils/History.h"

#include "services/Dropbox.h"
#include "services/Google.h"
#include "services/Server.h"
#include "services/Yandex.h"

#include "services/lib/UploadService.h"

// #include "ui/Overlay.h"
#include "ui/OverlayView.h"
#include "ui/SettingsForm.h"
#include "ui/TrayIcon.h"
#include "ui/Updater.h"

#include "utils/Settings.h"

#include <QObject>

/**
 * Common context
 * It contains current state of the running application
 * Singleton
 */
class Context : public QObject {
    Q_OBJECT

public:
    static Context& getInstance();

    // Overlay overlay;
    OverlayView overlayView;
    Updater updater;

    /**
     * Current selected service for uploading screenshots
     */
    UploadService uploadService;

    /**
     * Settings
     */
    Settings settings;

    /**
     * Ui
     */
    TrayIcon trayIcon;
    SettingsForm settingsForm;

    /**
     * Services
     */
    Dropbox dropbox;
    Google google;
    Server server;
    Yandex yandex;

    /**
     * History of screenshots
     */
    History history;

private:
    Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
};

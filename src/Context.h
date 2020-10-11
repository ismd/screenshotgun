#pragma once

#include "App.h"

#include "utils/History.h"

#include "services/Clipboard.h"
#include "services/Dropbox.h"
#include "services/Google.h"
#include "services/Server.h"
#include "services/Yandex.h"

#include "services/lib/UploadService.h"

#include "ui/ItemManager.h"
#include "ui/OverlayView.h"
#include "ui/SettingsForm.h"
#include "ui/Toolbar.h"
#include "ui/TrayIcon.h"
// #include "ui/Updater.h"

#include "utils/Settings.h"

#include <QObject>

/**
 * Common context
 * Contains current state of the running application
 * Singleton
 */
class Context : public QObject {
    Q_OBJECT

public:
    static Context& getInstance();

    App* app;

    OverlayView* overlayView;
    // FIXME
    // Updater updater;

    /**
     * Current selected service for uploading screenshots
     */
    UploadService uploadService;

    /**
     * Settings
     */
    Settings* settings;

    /**
     * Ui
     */
    Toolbar* toolbar;
    TrayIcon* trayIcon;
    SettingsForm* settingsForm;

    /**
     * Services
     */
    Dropbox* dropbox;
    Google* google;
    Server* server;
    Yandex* yandex;
    Clipboard* clipboard;

    /**
     * History of screenshots
     */
    History* history;

    ItemManager* itemManager;

private:
    Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
};

cmake_minimum_required(VERSION 3.5.1)
project(screenshotgun)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/ui")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#if(CMAKE_VERSION VERSION_LESS "3.7.0")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#endif()

find_package(Qt5 COMPONENTS Gui Network Widgets REQUIRED)

set(SOURCE_FILES
    resources/res.qrc
    src/main.cpp

    src/App.cpp
    src/App.h
    src/Context.cpp
    src/Context.h

    # Items
    src/items/AbstractItem.cpp
    src/items/AbstractItem.h
    src/items/ArrowItem.cpp
    src/items/ArrowItem.h
    src/items/LineItem.cpp
    src/items/LineItem.h
    src/items/RectItem.cpp
    src/items/RectItem.h
    src/items/EllipseItem.cpp
    src/items/EllipseItem.h
    src/items/VisibleAreaItem.cpp
    src/items/VisibleAreaItem.h

    # Services
    src/services/Clipboard.cpp
    src/services/Clipboard.h
    src/services/Dropbox.cpp
    src/services/Dropbox.h
    src/services/Google.cpp
    src/services/Google.h
    src/services/Server.cpp
    src/services/Server.h
    src/services/Yandex.cpp
    src/services/Yandex.h

    src/services/lib/AbstractService.cpp
    src/services/lib/AbstractService.h
    src/services/lib/generateFilename.cpp
    src/services/lib/generateFilename.h
    src/services/lib/UploadService.h

    # Ui
    src/ui/ItemManager.cpp
    src/ui/ItemManager.h
    src/ui/OAuth.cpp
    src/ui/OAuth.h
    src/ui/OverlayView.cpp
    src/ui/OverlayView.h
    src/ui/SettingsForm.cpp
    src/ui/SettingsForm.h
    src/ui/Toolbar.cpp
    src/ui/Toolbar.h
    src/ui/TrayIcon.cpp
    src/ui/TrayIcon.h
    # src/ui/Updater.cpp
    # src/ui/Updater.h

    # Utils
    src/utils/AutoStartup.cpp
    src/utils/AutoStartup.h
    src/utils/History.cpp
    src/utils/History.h
    src/utils/Settings.cpp
    src/utils/Settings.h
    src/utils/System.cpp
    src/utils/System.h
)

file(READ CHANGELOG.txt CHANGELOG_TEXT)
configure_file(src/utils/Changelog.h.in src/utils/Changelog.h)
list(APPEND SOURCE_FILES src/utils/Changelog.h)

# For CLion
include_directories(cmake-build-debug)

# macOS
if(APPLE)
    include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

    add_executable(screenshotgun MACOSX_BUNDLE ${SOURCE_FILES})
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Gui Qt5::Network)

# Linux
elseif(UNIX)
    find_package(X11 REQUIRED)

    list(APPEND SOURCE_FILES
        src/qxt/qxtglobal.h
        src/qxt/qxtglobalshortcut.h
        src/qxt/qxtglobalshortcut_p.h
        src/qxt/qxtglobalshortcut.cpp
        src/qxt/qxtglobalshortcut_x11.cpp)

    if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release" OR NOT DEFINED STATIC_BUILD OR NOT ${STATIC_BUILD})
        include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

        add_executable(screenshotgun ${SOURCE_FILES})
        target_link_libraries(screenshotgun X11 Qt5::Widgets Qt5::Gui Qt5::Network)
    else()
        include_directories(${ADDITIONAL_INCLUDE})

        link_directories(${QT5_PATH}/lib
            ${QT5_PATH}/plugins/platforms
            ${QT5_PATH}/qtbase/src/plugins/platforms/xcb/xcb-static
            ${QT5_PATH}/plugins/xcbglintegrations
            ${QT5_PATH}/qtbase/src/plugins/platforms/xcb/gl_integrations/xcb_egl/xcb-static
            ${QT5_PATH}/qtbase/src/plugins/platforms/xcb/gl_integrations/xcb_glx/xcb-static
            ${QT5_PATH}/plugins/imageformats
            ${QT5_PATH}/plugins/egldeviceintegrations)

        list(APPEND SOURCE_FILES src/plugins.cpp)

        add_executable(screenshotgun ${SOURCE_FILES})
        target_link_libraries(screenshotgun
            gobject-2.0 qwayland-egl wayland-egl qwayland-generic Qt5WaylandClient wayland-client wayland-cursor qxcb
            qxcb-egl-integration qxcb-glx-integration Qt5XcbQpa Xi SM ICE xcb-static qdds qicns qico qjp2 jasper qmng
            mng qtga qtiff tiff qwbmp qwebp webp qeglfs-kms-integration drm gbm qeglfs-x11-integration X11-xcb xcb
            Qt5EglDeviceIntegration Qt5PlatformSupport fontconfig freetype Qt5DBus Xrender Xext X11 input xkbcommon
            udev mtdev qtharfbuzzng Qt5::Core icui18n icuuc icudata qtpcre m dl gthread-2.0 -pthread glib-2.0 rt EGL GL
            pthread Qt5::Widgets Qt5::Gui Qt5::Network proxy)
    endif()

    install(TARGETS screenshotgun RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_SOURCE_DIR}/resources/dist/screenshotgun.desktop"
        DESTINATION share/applications)
    install(FILES "${CMAKE_SOURCE_DIR}/resources/dist/screenshotgun.png"
        DESTINATION share/pixmaps)

# Windows
elseif(WIN32)
    add_executable(screenshotgun WIN32 ${SOURCE_FILES})
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Gui Qt5::Network)
endif()

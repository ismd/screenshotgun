cmake_minimum_required(VERSION 2.8)
project(screenshotgun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
    resources/res.qrc
    src/modes/AbstractMode.cpp
    src/modes/AbstractMode.h
    src/modes/ArrowMode.cpp
    src/modes/ArrowMode.h
    src/modes/LineMode.cpp
    src/modes/LineMode.h
    src/modes/RectMode.cpp
    src/modes/RectMode.h
    src/modes/EllipseMode.cpp
    src/modes/EllipseMode.h
    src/modes/TextMode.cpp
    src/modes/TextMode.h
    src/modes/VisibleAreaMode.cpp
    src/modes/VisibleAreaMode.h
    src/modes/TextArea.cpp
    src/modes/TextArea.h
    src/Autostartup.cpp
    src/Autostartup.h
    src/Toolbar.cpp
    src/Toolbar.h
    src/App.cpp
    src/App.h
    src/main.cpp
    src/services/Server.cpp
    src/services/Server.h
    src/Settings.cpp
    src/Settings.h
    src/SettingsForm.cpp
    src/SettingsForm.h
    src/TrayIcon.cpp
    src/TrayIcon.h
    src/AppView.cpp
    src/AppView.h
    src/Updater_win.cpp
    src/Updater_win.h
    src/History.cpp
    src/History.h
    src/services/Yandex.cpp
    src/services/Yandex.h
    src/services/Dropbox.cpp
    src/services/Dropbox.h
    src/services/Google.cpp
    src/services/Google.h
    src/OAuth.cpp
    src/OAuth.h
    src/services/ServiceHelper.cpp
    src/services/ServiceHelper.h)

find_package(Qt5 COMPONENTS Gui Network Widgets REQUIRED)

qt5_wrap_ui(SOURCE_FILES
    ui/OAuth.ui
    ui/Settings.ui
    ui/Toolbar.ui
    ui/Update.ui)

if(APPLE)
    include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

    add_executable(screenshotgun ${SOURCE_FILES})
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Gui Qt5::Network)
else(UNIX)
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
else(WIN32)
    add_executable(screenshotgun WIN32 ${SOURCE_FILES})
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Gui Qt5::Network)
endif()

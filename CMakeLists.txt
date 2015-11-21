cmake_minimum_required(VERSION 2.8)
project(screenshotgun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
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
    src/Autostartup.cpp
    src/Autostartup.h
    src/Toolbar.cpp
    src/Toolbar.h
    src/App.cpp
    src/App.h
    src/main.cpp
    src/Server.cpp
    src/Server.h
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
    src/History.h src/modes/TextArea.cpp src/modes/TextArea.h)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    find_package(Qt5 COMPONENTS Gui REQUIRED)
    include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

    list(APPEND SOURCE_FILES
        src/qxt/qxtglobal.h
        src/qxt/qxtglobalshortcut.h
        src/qxt/qxtglobalshortcut_p.h
        src/qxt/qxtglobalshortcut.cpp
        src/qxt/qxtglobalshortcut_x11.cpp)
endif()

qt5_wrap_ui(UIS_HDRS
    ui/Toolbar.ui
    ui/Update.ui
    ui/Settings.ui)

if(UNIX AND NOT APPLE)
    add_executable(screenshotgun ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun X11 Qt5::Widgets Qt5::Network)

    install(TARGETS screenshotgun DESTINATION bin)
    install(FILES "${CMAKE_SOURCE_DIR}/dist/screenshotgun.desktop"
        DESTINATION share/applications)
    install(FILES "${CMAKE_SOURCE_DIR}/dist/screenshotgun.png"
        DESTINATION share/pixmaps)
else(WIN32)
    add_executable(screenshotgun WIN32 ${SOURCE_FILES} ${UIS_HDRS} resources/res.qrc)
    target_link_libraries(screenshotgun Qt5::Widgets Qt5::Network)
endif()

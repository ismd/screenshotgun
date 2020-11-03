#!/bin/bash

# Qt Installer Framework
if [ -z "$(ls -A $HOME/qt-installer-framework/build)" ]; then
    tar xf $HOME/qt-installer-framework-opensource-src-3.2.2.tar.gz -C /c/qt-installer-framework

    mkdir /c/qt-installer-framework/build
    cd /c/qt-installer-framework/build

    qmake CONFIG+=release ../installerfw.pro
    make
fi

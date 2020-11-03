#!/bin/bash

# Qt Installer Framework
if [ -z "$(ls -A $HOME/qt-installer-framework/build)" ]; then
    tar xf $HOME/qt-installer-framework-opensource-src-3.2.2.tar.gz -C $HOME/qt-installer-framework

    mkdir $HOME/qt-installer-framework/build
    cd $HOME/qt-installer-framework/build

    qmake CONFIG+=release ../installerfw.pro
    make
    make install
fi

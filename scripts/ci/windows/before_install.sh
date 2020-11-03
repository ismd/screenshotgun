#!/bin/bash

# Qt
if [ -z "$(ls -A /c/Qt)" ]; then
    choco install pip
    py -m pip install --upgrade pip
    py -m pip install aqtinstall
    py -m aqt install --outputdir /c/Qt 5.15.2 windows desktop win64_mingw81
fi

# Qt Installer Framework
if [ -z "$(ls -A /c/qt-installer-framework)" ]; then
    wget -q http://download.qt.io/official_releases/qt-installer-framework/3.2.2/qt-installer-framework-opensource-src-3.2.2.tar.gz -P $HOME
fi

#!/bin/bash

# Qt
if [ -z "$(ls -A /c/Qt)" ]; then
    choco install pip
    py -m pip install --upgrade pip
    py -m pip install aqtinstall
    py -m aqt install -O /c/Qt 5.15.2 windows desktop win64_mingw81
fi

# Qt Installer Framework
if [ -z "$(ls -A /c/qt-installer-framework)" ]; then
    py -m aqt tool -O /c/qt-installer-framework windows tools_ifw 4.0 qt.tools.ifw.40
fi

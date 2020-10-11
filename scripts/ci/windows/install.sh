#!/bin/bash

if [ -z "$(ls -A $HOME/Qt)" ]; then
    $HOME/qt-opensource-windows-x86-5.13.2.exe --script $TRAVIS_BUILD_DIR/scripts/ci/windows/scripts/qt_installer_windows.qs
fi

#!/bin/bash

if [ -z "$(ls -A /c/Qt)" ]; then
    wget -q https://download.qt.io/official_releases/qt/5.13/5.13.2/qt-opensource-windows-x86-5.13.2.exe -P $HOME
fi

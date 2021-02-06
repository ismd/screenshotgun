#!/bin/bash

if [ -z "$(ls -A /c/Qt)" ]; then
    choco install pip
    py -m pip install --upgrade pip
    py -m pip install aqtinstall
    py -m aqt install --outputdir /c/Qt 5.15.2 windows desktop win64_mingw81
fi

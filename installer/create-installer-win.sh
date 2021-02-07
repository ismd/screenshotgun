#!/bin/bash

OUTPUT_FILE=$1

/c/qt-installer-framework/Tools/QtInstallerFramework/4.0/bin/binarycreator.exe \
    -n -v \
    -c $TRAVIS_BUILD_DIR/installer/config-win/config.xml \
    -p $TRAVIS_BUILD_DIR/installer/packages-win \
    $OUTPUT_FILE

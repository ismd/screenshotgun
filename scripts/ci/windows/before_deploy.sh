#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cd $TRAVIS_BUILD_DIR/build
7za a -tzip $RELEASE_DIR/screenshotgun_windows.zip screenshotgun.exe

#!/bin/bash

RELEASE_DIR=$HOME/release

mkdir -p $RELEASE_DIR
cd $TRAVIS_BUILD_DIR/build
7z a -tzip $RELEASE_DIR/screenshotgun_windows.zip screenshotgun.exe

echo "!!!!!!!!!!!!!!!!!!!!!!"
cd ~
pwd

echo '2'
ls -l /c/Users/travis/release/screenshotgun_windows.zip

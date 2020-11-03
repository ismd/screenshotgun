#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/local/opt/qt ..
cmake --build .
strip screenshotgun.app/Contents/MacOS/screenshotgun

# Installer
sed -i '.bak' s/{VERSION}/${TRAVIS_TAG}/g $TRAVIS_BUILD_DIR/installer/config-osx/config.xml
mv $TRAVIS_BUILD_DIR/installer/config-osx/config.xml.bak $TRAVIS_BUILD_DIR/installer/config-osx/config.xml
echo "PATH!!!!!!"
echo $PATH
$TRAVIS_BUILD_DIR/installer/create-installer-osx.sh $HOME/release/ScreenshotgunInstaller

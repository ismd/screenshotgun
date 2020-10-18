#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cd $TRAVIS_BUILD_DIR/build
zip $RELEASE_DIR/screenshotgun_linux.zip screenshotgun

cd $RELEASE_DIR

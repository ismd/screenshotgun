#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cd $TRAVIS_BUILD_DIR/build
zip -r $RELEASE_DIR/screenshotgun_osx.app.zip screenshotgun.app

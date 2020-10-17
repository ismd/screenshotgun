#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
zip -r $RELEASE_DIR/screenshotgun_osx.app.zip $TRAVIS_BUILD_DIR/build/screenshotgun.app

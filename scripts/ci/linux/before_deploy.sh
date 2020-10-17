#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cp $TRAVIS_BUILD_DIR/build/screenshotgun $RELEASE_DIR/screenshotgun_linux

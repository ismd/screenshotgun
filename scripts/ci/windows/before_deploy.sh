#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cp $TRAVIS_BUILD_DIR/build/screenshotgun.exe $RELEASE_DIR/screenshotgun.exe
ls -l $TRAVIS_BUILD_DIR/build
ls -l $RELEASE_DIR

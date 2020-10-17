#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

pwd
ls -l $TRAVIS_BUILD_DIR
ls -l $TRAVIS_BUILD_DIR/build
ls -l $TRAVIS_BUILD_DIR/build/Release

mkdir -p $RELEASE_DIR
cp $TRAVIS_BUILD_DIR/build/Release/screenshotgun.exe $RELEASE_DIR/screenshotgun.exe

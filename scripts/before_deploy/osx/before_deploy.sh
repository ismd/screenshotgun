#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

ls -l $TRAVIS_BUILD_DIR/build
ls -l $TRAVIS_BUILD_DIR/build/screenshotgun.app

mkdir -p $RELEASE_DIR
cp $TRAVIS_BUILD_DIR/build/screenshotgun.app $RELEASE_DIR/screenshotgun_osx.app

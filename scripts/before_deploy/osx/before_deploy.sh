#!/bin/bash

RELEASE_DIR=$HOME/release/$TRAVIS_OS_NAME

mkdir -p $RELEASE_DIR
cp -r $TRAVIS_BUILD_DIR/build/screenshotgun.app $RELEASE_DIR/screenshotgun_osx.app

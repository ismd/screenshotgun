#!/bin/bash

RELEASE_DIR=$HOME/release

mkdir -p $RELEASE_DIR
cd $TRAVIS_BUILD_DIR/build
zip -r $RELEASE_DIR/screenshotgun_osx.zip screenshotgun.app
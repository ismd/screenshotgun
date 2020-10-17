#!/bin/bash

RELEASE_DIR=$HOME/release/github/linux

mkdir -p $RELEASE_DIR
cp $TRAVIS_BUILD_DIR/build/screenshotgun $RELEASE_DIR

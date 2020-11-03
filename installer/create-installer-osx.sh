#!/bin/bash

OUTPUT_FILE=$1

binarycreator -n -v -c $TRAVIS_BUILD_DIR/installer/config-osx/config.xml -p $TRAVIS_BUILD_DIR/installer/packages-osx $OUTPUT_FILE

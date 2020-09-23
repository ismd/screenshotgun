#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build && cd $TRAVIS_BUILD_DIR/build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
strip screenshotgun

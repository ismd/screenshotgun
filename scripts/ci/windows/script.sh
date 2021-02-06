#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/c/Qt/5.15.2/mingw81_64 ..
cmake --build . --config Release

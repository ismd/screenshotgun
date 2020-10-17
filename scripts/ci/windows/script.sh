#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build
ls -l /c/Qt/5.13.2
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/c/Qt/5.13.2/mingw73_64 ..
ls -la
cmake  --build . --config Release
ls -la

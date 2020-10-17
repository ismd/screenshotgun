#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build
ls -l /c/Qt/5.13.2
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\Qt\5.13.2\msvc2017" ..
cmake --config Release --target ALL_BUILD --build .
ls -la

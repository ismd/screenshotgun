#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\Qt\5.13.2\msvc2017" ..
cmake --config Release --target ALL_BUILD --build .
devenv.exe screenshotgun.sln /build Debug /project ALL_BUILD

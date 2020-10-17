#!/bin/bash

mkdir $TRAVIS_BUILD_DIR/build
cd $TRAVIS_BUILD_DIR/build
ls -l /
ls -l /mnt
ls -l $HOME
ls -l $HOME/..
ls -l /c
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\Qt\5.13.2\msvc2017" ..
ls -la
cmake  --build . --config Release
ls -la

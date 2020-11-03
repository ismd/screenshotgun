#!/bin/bash

openssl aes-256-cbc -K $encrypted_33b5e9db54c1_key -iv $encrypted_33b5e9db54c1_iv -in $TRAVIS_BUILD_DIR/scripts/deploy/data.tar.enc -out $TRAVIS_BUILD_DIR/scripts/deploy/data.tar -d
tar xvf $TRAVIS_BUILD_DIR/scripts/deploy/data.tar -C $TRAVIS_BUILD_DIR/scripts/deploy

brew link qt --force

# Qt Installer Framework
if [ -z "$(ls -A $HOME/qt-installer-framework)" ]; then
    wget -q http://download.qt.io/official_releases/qt-installer-framework/3.2.2/qt-installer-framework-opensource-src-3.2.2.tar.gz -P $HOME
fi

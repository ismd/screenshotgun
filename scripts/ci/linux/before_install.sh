#!/bin/bash

sudo apt-get update
openssl aes-256-cbc -K $encrypted_33b5e9db54c1_key -iv $encrypted_33b5e9db54c1_iv -in $TRAVIS_BUILD_DIR/scripts/deploy/data.tar.enc -out $TRAVIS_BUILD_DIR/scripts/deploy/data.tar -d
tar xvf $TRAVIS_BUILD_DIR/scripts/deploy/data.tar

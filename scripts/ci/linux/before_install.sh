#!/bin/bash

sudo apt-get update
openssl aes-256-cbc -K $encrypted_55f6cc107eaa_key -iv $encrypted_55f6cc107eaa_iv -in $TRAVIS_BUILD_DIR/deploy/data.tar.enc -out $TRAVIS_BUILD_DIR/deploy/data.tar -d
tar xvf $TRAVIS_BUILD_DIR/deploy/data.tar

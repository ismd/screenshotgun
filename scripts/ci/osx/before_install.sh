#!/bin/bash

openssl aes-256-cbc -K $encrypted_55f6cc107eaa_key -iv $encrypted_55f6cc107eaa_iv -in $TRAVIS_BUILD_DIR/scripts/deploy/data.tar.enc -out $TRAVIS_BUILD_DIR/scripts/deploy/data.tar -d
tar xvf $TRAVIS_BUILD_DIR/scripts/deploy/data.tar

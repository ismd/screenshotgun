#!/bin/bash
VERSION=$1

# AUR
docker build --build-arg VERSION=$VERSION $TRAVIS_BUILD_DIR/deploy/arch

#!/bin/bash
VERSION=$1
VERSION=${VERSION#"v"}

# AUR
docker build --build-arg VERSION=$VERSION --security-opt seccomp:unconfined $TRAVIS_BUILD_DIR/deploy/arch

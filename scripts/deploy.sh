#!/bin/bash
VERSION=$1
VERSION=${VERSION#"v"}

# AUR
docker build --build-arg VERSION=$VERSION --secomp-profile $TRAVIS_BUILD_DIR/deploy/arch/secomp-profile.json $TRAVIS_BUILD_DIR/deploy/arch

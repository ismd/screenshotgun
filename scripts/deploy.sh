#!/bin/bash
VERSION=${1#"v"}

# AUR
docker run -e VERSION=$VERSION -v $TRAVIS_BUILD_DIR/deploy/arch:/deploy base/archlinux /deploy/arch/deploy.sh

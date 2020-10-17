#!/bin/bash
set -e
set -o pipefail

VERSION=${1#"v"}

# LAUNCHPAD
$TRAVIS_BUILD_DIR/scripts/deploy/launchpad/deploy.sh

# AUR
docker run -e VERSION=$VERSION -v $TRAVIS_BUILD_DIR/scripts/deploy:/deploy --privileged archlinux/base /deploy/aur/deploy.sh

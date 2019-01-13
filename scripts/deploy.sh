#!/bin/bash
set -e
set -o pipefail

export VERSION=${1#"v"}

# LAUNCHPAD
$TRAVIS_BUILD_DIR/deploy/launchpad/deploy.sh

# AUR
docker run -e VERSION=$VERSION -v $TRAVIS_BUILD_DIR/deploy:/deploy --privileged base/archlinux /deploy/aur/deploy.sh

#!/bin/bash
set -e
set -o pipefail

VERSION=${1#"v"}

# AUR
docker run -e VERSION=$VERSION -v $TRAVIS_BUILD_DIR/deploy:/deploy --privileged base/archlinux /deploy/arch/deploy.sh

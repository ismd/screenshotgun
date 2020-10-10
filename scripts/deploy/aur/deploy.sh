#!/bin/bash
set -e
set -o pipefail

DEPLOY_DIR=/deploy
BUILD_DIR=/build

pacman -Sy
pacman -S --needed --noconfirm base-devel git openssh

useradd -m build
echo "build ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

chown -R build $DEPLOY_DIR
mkdir $BUILD_DIR
chown build $BUILD_DIR

sudo VERSION=$VERSION -u build $DEPLOY_DIR/aur/deploy_build.sh

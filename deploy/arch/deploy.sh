#!/bin/bash
set -e
set -o pipefail

DEPLOY_DIR=/deploy
BUILD_DIR=/build

pacman -Sy
pacman -S --needed --noconfirm base-devel git openssh

useradd -m build
echo "build ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

chown -R build /deploy
mkdir /build && chown build /build

sudo VERSION=$VERSION -u build /deploy/deploy_build.sh

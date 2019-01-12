#!/bin/bash
set -e
set -o pipefail

DEPLOY_DIR=/deploy
BUILD_DIR=/build

mkdir ~/.ssh
cp $DEPLOY_DIR/aur/aur ~/.ssh/id_rsa
chmod 600 ~/.ssh/id_rsa
ssh-keyscan -t rsa aur.archlinux.org >> ~/.ssh/known_hosts

cd $BUILD_DIR
git clone ssh://aur@aur.archlinux.org/screenshotgun-git.git
cd screenshotgun-git

git config user.email "zzismd@gmail.com"
git config user.name "Vladimir Kosteley"

cp $DEPLOY_DIR/aur/PKGBUILD PKGBUILD
AUR_VERSION=`echo $VERSION | sed 's/-/_/g'`
sed -i -e "s/{AUR_VERSION}/$AUR_VERSION/g" PKGBUILD
sed -i -e "s/{VERSION}/$VERSION/g" PKGBUILD
makepkg --printsrcinfo > .SRCINFO

# Checking build
cp -r $BUILD_DIR/screenshotgun-git $BUILD_DIR/build
cd $BUILD_DIR/build
makepkg -s --needed --noconfirm

# Committing and pushing
cd $BUILD_DIR/screenshotgun-git
git commit -am "Version: $VERSION"
git push

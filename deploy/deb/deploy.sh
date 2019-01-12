#!/bin/bash
set -e
set -o pipefail

DEPLOY_DIR=$HOME/deploy

sudo apt-get install bzr-builddeb dh-make dput pbuilder ubuntu-dev-tools

bzr whoami "Vladimir Kosteley <zzismd@gmail.com>"
gpg --import $TRAVIS_BUILD_DIR/deploy/deb/launchpad.asc
gpg --import $TRAVIS_BUILD_DIR/deploy/deb/launchpad_public.asc

mkdir -p $DEPLOY_DIR/launchpad

cd $DEPLOY_DIR/launchpad
bzr dh-make --bzr-only screenshotgun $VERSION $TRAVIS_BUILD_DIR

cd $DEPLOY_DIR/launchpad/screenshotgun
dh_make -y -s -p screenshotgun_$VERSION
rm -rf debian
cp -r $TRAVIS_BUILD_DIR/deploy/deb/debian debian
sed -i -e "s/{version}/$VERSION/g" debian/changelog
sed -i -e "s/{date}/`date +'%a, %d %b %Y %H:%M:%S +0300'`/g" debian/changelog
sed -i -e "s/{distribution}/bionic/g" debian/changelog

bzr add debian
bzr builddeb -S

cd $DEPLOY_DIR/launchpad/build-area
pbuilder-dist bionic create
pbuilder-dist bionic build screenshotgun_$VERSION-1.dsc
dput ppa:ismd/screenshotgun screenshotgun_$VERSION-1_source.changes

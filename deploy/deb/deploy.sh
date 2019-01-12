#!/bin/bash
set -e
set -o pipefail

sudo apt-get install dh-make bzr-builddeb

DEPLOY_DIR=$HOME/deploy

mkdir -p $DEPLOY_DIR/launchpad

cd $DEPLOY_DIR/launchpad
ls -l $TRAVIS_BUILD_DIR
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

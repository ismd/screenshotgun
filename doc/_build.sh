#!/bin/bash
if [[ ! $1 ]]; then
  echo "Usage: $0 <version>"
  exit 0
fi

SRC_PATH=/home/ismd/src/screenshotgun
VERSION=$1

BUILD_PATH_UBUNTU_64=/home/ismd/build/screenshotgun-ubuntu-64
BUILD_PATH_WINDOWS_32=/home/ismd/build/screenshotgun-windows-32
BUILD_PATH_DEB_64=/home/ismd/build/deb-64

DIST_PATH=/srv/screenshotgun.com/public/dist
PPA_PATH=/home/ismd/repos/ppa

DEB_64_FILENAME=screenshotgun_amd64.deb

rm -rf $BUILD_PATH_UBUNTU_64
rm -rf $BUILD_PATH_WINDOWS_32
mkdir $BUILD_PATH_UBUNTU_64
mkdir $BUILD_PATH_WINDOWS_32

echo "*** Updating working copy ***"
cd $SRC_PATH
git pull

if [[ $(git status -s | wc -l) -eq 0 ]]; then
  echo -e "\n*** No changes ***"
  exit 228
fi

# Compiling for ubuntu 64
echo -e "\n*** Compiling for ubuntu 64 ***"

cd $BUILD_PATH_UBUNTU_64
cmake $SRC_PATH
cmake --build . || exit $?
strip screenshotgun

# Compiling for windows 32
echo -e "\n*** Compiling for windows 32 ***"

MXE_PATH=/home/ismd/src/mxe
PATH=$MXE_PATH/usr/bin:$PATH

cd $BUILD_PATH_WINDOWS_32
cmake $SRC_PATH
cmake --build . -- -j1 -DCMAKE_TOOLCHAIN_FILE=${MXE_PATH}/usr/i686-w64-mingw32.static/share/cmake/mxe-conf.cmake || exit $?

# Deb 64
cp $BUILD_PATH_UBUNTU_64/screenshotgun $BUILD_PATH_DEB_64/usr/bin/screenshotgun
cd $BUILD_PATH_DEB_64
sed -i "s/Version: .*/Version: $VERSION/g" DEBIAN/control

SIZE_DEB_64=`du -s usr | sed -s 's/\(.*\)\s.*/\1/'`
sed -i "s/Installed-Size: .*/Installed-Size: $SIZE_DEB_64/g" DEBIAN/control
find . -type f ! -regex '.*.hg.*' ! -regex '.*?debian-binary.*' ! -regex '.*?DEBIAN.*' -printf '%P ' | xargs md5sum > DEBIAN/md5sums

cp $SRC_PATH/dist/screenshotgun.desktop $BUILD_PATH_DEB_64/usr/share/applications/screenshotgun.desktop
cp $SRC_PATH/dist/screenshotgun.png $BUILD_PATH_DEB_64/usr/share/pixmaps/screenshotgun.png

cd ..
fakeroot dpkg-deb --build deb-64
cp deb-64.deb $PPA_PATH/$DEB_64_FILENAME

# PPA
cd $PPA_PATH
reprepro remove trusty screenshotgun
reprepro includedeb trusty $DEB_64_FILENAME

# Copying new versions
mv $PPA_PATH/$DEB_64_FILENAME $DIST_PATH/$DEB_64_FILENAME
cp $BUILD_PATH_WINDOWS_32/release/screenshotgun.exe $DIST_PATH/screenshotgun.exe

echo -e "\n*** Success ***"

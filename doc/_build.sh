#!/bin/bash
SRC_PATH=/home/ismd/src/screenshotgun

BUILD_PATH_UBUNTU_64=/home/ismd/build/screenshotgun-ubuntu-64
BUILD_PATH_WINDOWS_32=/home/ismd/build/screenshotgun-windows-32

DIST_PATH=/srv/screenshotgun.com/public/dist
PPA_PATH=/home/ismd/repos/ppa

UBUNTU_64_OUTPUT_BIN=screenshotgun
WINDOWS_32_OUTPUT_BIN=screenshotgun.exe

UBUNTU_64_BIN=screenshotgun
WINDOWS_32_BIN=screenshotgun.exe

VERSION_FILE=$DIST_PATH/version

rm -rf $BUILD_PATH_UBUNTU_64
rm -rf $BUILD_PATH_WINDOWS_32
mkdir $BUILD_PATH_UBUNTU_64
mkdir $BUILD_PATH_WINDOWS_32

cd $SRC_PATH
git checkout -- `find . -name const.h`
echo "*** Updating working copy ***"
git pull

LAST_VERSION=`git rev-list HEAD --count`
CURRENT_VERSION=`cat $VERSION_FILE`

if [ $LAST_VERSION == $CURRENT_VERSION ]; then
  echo -e "\n*** Already last version ($LAST_VERSION) ***"
  exit 228
fi

sed -i "s/\#define VERSION \".*\"/\#define VERSION \"$LAST_VERSION\"/g" `find $SRC_PATH -name const.h`

# Compiling for ubuntu 64
echo -e "\n*** Compiling for ubuntu 64 ***"

#docker run \
#       -v $SRC_PATH:/home/ismd/src/screenshotgun:ro \
#       -v $BUILD_PATH_UBUNTU_64:/home/ismd/build-output \
#       ismd/screenshotgun-ubuntu /home/ismd/bin/build.sh

#cd $SRC_PATH
#qmake -config release -o $BUILD_PATH_UBUNTU_64/Makefile

cd $BUILD_PATH_UBUNTU_64
cmake $SRC_PATH
cmake --build . --target all
#make || exit $?
strip $UBUNTU_64_OUTPUT_BIN

# Compiling for windows 32
MXE_PATH=/home/ismd/src/mxe

#cd $SRC_PATH
#$MXE_PATH/usr/bin/i686-w64-mingw32.static-qmake-qt5 -config release -o $BUILD_PATH_WINDOWS_32/Makefile

cd $BUILD_PATH_WINDOWS_32
PATH=$MXE_PATH/usr/bin:$PATH
echo -e "\n*** Compiling for windows 32 ***"
#make || exit $?
cmake $SRC_PATH
cmake --build . --target all -- -j 1 -DCMAKE_TOOLCHAIN_FILE=${MXE_PATH}/usr/i686-w64-mingw32.static/share/cmake/mxe-conf.cmake

# Clearing
cd $SRC_PATH
git checkout -- `find . -name const.h`

# Deb 64
DEB_64_FILENAME=screenshotgun_${LAST_VERSION}_amd64.deb

cp $BUILD_PATH_UBUNTU_64/$UBUNTU_64_OUTPUT_BIN /home/ismd/build/deb-64/usr/bin/$UBUNTU_64_BIN
cd /home/ismd/build/deb-64
sed -i "s/Version: .*/Version: $LAST_VERSION/g" DEBIAN/control

SIZE_DEB_64=`du -s usr | sed -s 's/\(.*\)\s.*/\1/'`
sed -i "s/Installed-Size: .*/Installed-Size: $SIZE_DEB_64/g" DEBIAN/control
find . -type f ! -regex '.*.hg.*' ! -regex '.*?debian-binary.*' ! -regex '.*?DEBIAN.*' -printf '%P ' | xargs md5sum > DEBIAN/md5sums

cp $SRC_PATH/dist/screenshotgun.desktop /home/ismd/build/deb-64/usr/share/applications/screenshotgun.desktop
cp $SRC_PATH/dist/screenshotgun.png /home/ismd/build/deb-64/usr/share/pixmaps/screenshotgun.png

cd ..
fakeroot dpkg-deb --build deb-64
cp deb-64.deb $PPA_PATH/$DEB_64_FILENAME

# PPA
cd $PPA_PATH
reprepro remove trusty screenshotgun
reprepro includedeb trusty $DEB_64_FILENAME

# Copying new versions
rm $DIST_PATH/*.deb
mv $PPA_PATH/$DEB_64_FILENAME $DIST_PATH/screenshotgun_amd64.deb
cp $BUILD_PATH_WINDOWS_32/release/$WINDOWS_32_OUTPUT_BIN $DIST_PATH/$WINDOWS_32_BIN

echo $LAST_VERSION > $VERSION_FILE
echo -e "\n*** Success ***"

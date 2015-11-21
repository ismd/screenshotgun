#!/bin/bash
if [[ ! $1 ]]; then
  echo "Usage: $0 <version>"
  exit 0
fi

SRC_PATH=/home/ismd/src/screenshotgun
VERSION=$1

#BUILD_PATH_LINUX_64=/home/ismd/build/screenshotgun-linux-64
BUILD_PATH_WINDOWS_32=/home/ismd/build/screenshotgun-windows-32
BUILD_PATH_DEB_64=/home/ismd/build/deb-64

DIST_PATH=/srv/screenshotgun.com/public/dist
PPA_PATH=/home/ismd/repos/ppa
ARCH_PATH=/home/ismd/src/screenshotgun-aur
DEB_64_FILENAME=screenshotgun_amd64.deb

#rm -rf $BUILD_PATH_LINUX_64
rm -rf $BUILD_PATH_WINDOWS_32
#mkdir $BUILD_PATH_LINUX_64
mkdir $BUILD_PATH_WINDOWS_32

echo "*** Updating working copy ***"
cd $SRC_PATH
git pull

#if [[ $(git status -s | wc -l) -eq 0 ]]; then
#  echo "*** No changes ***"
#  exit 228
#fi

# Compiling for linux 64
echo -e "\n*** Compiling for linux 64 ***"

#cd $BUILD_PATH_LINUX_64
#cmake $SRC_PATH -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$BUILD_PATH_DEB_64/usr
#cmake --build . || exit $?
#make install/strip

docker run -i -v $SRC_PATH:$SRC_PATH:ro -v $BUILD_PATH_DEB_64/usr:/home/ismd/build-output ismd/screenshotgun-ubuntu /home/ismd/bin/build.sh

# Deb 64
echo -e "\n*** Making deb 64 ***"

cd $BUILD_PATH_DEB_64
sed -i "s/Version: .*/Version: $VERSION/g" DEBIAN/control

SIZE_DEB_64=`du -s usr | sed -s 's/\(.*\)\s.*/\1/'`
sed -i "s/Installed-Size: .*/Installed-Size: $SIZE_DEB_64/g" DEBIAN/control
find . -type f ! -regex '.*.hg.*' ! -regex '.*?debian-binary.*' ! -regex '.*?DEBIAN.*' -printf '%P ' | xargs md5sum > DEBIAN/md5sums

cd ..
fakeroot dpkg-deb --build deb-64
cp deb-64.deb $PPA_PATH/$DEB_64_FILENAME

# PPA
echo -e "\n*** PPA ***"

cd $PPA_PATH
reprepro remove trusty screenshotgun
reprepro includedeb trusty $DEB_64_FILENAME

mv $PPA_PATH/$DEB_64_FILENAME $DIST_PATH/$DEB_64_FILENAME

# Compiling for windows 32
echo -e "\n*** Compiling for windows 32 ***"

MXE_PATH=/home/ismd/src/mxe
PATH=$MXE_PATH/usr/bin:$PATH

cd $BUILD_PATH_WINDOWS_32
cmake $SRC_PATH -DCMAKE_TOOLCHAIN_FILE=${MXE_PATH}/usr/i686-w64-mingw32.shared/share/cmake/mxe-conf.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build . || exit $?

# Arch
echo -e "\n*** Arch AUR ***"

cd $ARCH_PATH
git pull
ARCH_VERSION=$(echo $VERSION | sed -e "s/-/_/g")
sed -i "s/pkgver = .*/pkgver = $ARCH_VERSION/g" $ARCH_PATH/.SRCINFO
sed -i "s/pkgver=.*/pkgver=$ARCH_VERSION/g" $ARCH_PATH/PKGBUILD
git commit -a -m "Version $ARCH_VERSION"
git push

# Qt installer
echo -e "\n*** Qt installer ***"

cp $BUILD_PATH_WINDOWS_32/screenshotgun.exe $SRC_PATH/installer/packages/screenshotgun/data/screenshotgun.exe
sed -i "s/<Version>.*<\/Version>/<Version>$VERSION<\/Version>/g" $SRC_PATH/installer/packages/screenshotgun/meta/package.xml
CURRENT_DATE=`date +%F`
sed -i "s/<ReleaseDate>.*<\/ReleaseDate>/<ReleaseDate>$CURRENT_DATE<\/ReleaseDate>/g" $SRC_PATH/installer/packages/screenshotgun/meta/package.xml
repogen --update-new-components -p $SRC_PATH/installer/packages $DIST_PATH/installer-repository

echo -e "\n*** Success ***"

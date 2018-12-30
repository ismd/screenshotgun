DEPLOY_DIR=/deploy
BUILD_DIR=/build

mkdir $BUILD_DIR && cd $BUILD_DIR
git clone ssh://aur@aur.archlinux.org/screenshotgun-git.git
cd screenshotgun-git
git config user.email "zzismd@gmail.com"
git config user.name "Vladimir Kosteley"

cp $DEPLOY_DIR/PKGBUILD PKGBUILD
AUR_VERSION=`echo $VERSION | sed 's/-/_/g'`
sed -i -e "s/{AUR_VERSION}/$AUR_VERSION/g" PKGBUILD
sed -i -e "s/{VERSION}/$VERSION/g" PKGBUILD
touch .SRCINFO
chmod 666 .SRCINFO
sudo -u build bash -c 'makepkg --printsrcinfo > .SRCINFO'
git commit -am "Version: $VERSION"
git push

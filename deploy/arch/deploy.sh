DEPLOY_DIR=/deploy
BUILD_DIR=/build

mkdir ~/.ssh
cp $DEPLOY_DIR/aur ~/.ssh/id_rsa
ssh-keyscan -t rsa aur.archlinux.org >> ~/.ssh/known_hosts

cd $BUILD_DIR
git clone ssh://aur@aur.archlinux.org/screenshotgun-git.git
cd screenshotgun-git

git config user.email "zzismd@gmail.com"
git config user.name "Vladimir Kosteley"

cp $DEPLOY_DIR/PKGBUILD PKGBUILD
AUR_VERSION=`echo $VERSION | sed 's/-/_/g'`
sed -i -e "s/{AUR_VERSION}/$AUR_VERSION/g" PKGBUILD
sed -i -e "s/{VERSION}/$VERSION/g" PKGBUILD
touch .SRCINFO
makepkg --printsrcinfo > .SRCINFO
git commit -am "Version: $VERSION"
makepkg -s --needed --noconfirm
git push

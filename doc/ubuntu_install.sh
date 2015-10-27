sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 0989698D105AEEBB
echo 'deb http://ubuntu.screenshotgun.com trusty main' | sudo tee --append /etc/apt/sources.list > /dev/null
sudo apt-get update
sudo apt-get install screenshotgun

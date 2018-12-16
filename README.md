# Screenshotgun
Open cross-platform screenshoter with cloud support and server part.  
With this application you can make screenshots, draw figures or write text and then upload to:  
* [screenshotgun.com](http://screenshotgun.com)
* Dropbox
* Google Drive
* Yandex.Disk
* Your own server

You can get open source server part and deploy it by yourself [github.com/ismd/screenshotgun-server](https://github.com/ismd/screenshotgun-server)
  
Download binaries for Windows, Linux and macOS from official site [screenshotgun.com](http://screenshotgun.com)   

![](https://github.com/ismd/screenshotgun/raw/master/resources/images/readme.png "")

## Install
#### Linux
###### Ubuntu 18.04, Ubuntu 16.04, Linux Mint
1. sudo add-apt-repository ppa:ismd/screenshotgun
2. sudo apt update
3. sudo apt install screenshotgun
###### Arch Linux
yaourt -S screenshotgun-git
#### macOS
[Download and drag'n'drop to Applications directory](http://screenshotgun.com/dist/Screenshotgun.dmg)
#### Windows
[Download and install](http://screenshotgun.com/dist/ScreenshotgunInstaller.exe)

## Build
You can simply use CLion with Qt5 libs under any operating system. Or you can build manually:
#### Linux
###### Ubuntu 16.04
1. sudo apt install build-essential git cmake qtbase5-dev qtbase5-private-dev
2. git clone https://github.com/ismd/screenshotgun.git
3. cd screenshotgun && mkdir build && cd build
4. cmake ..
5. cmake --build .
###### Arch Linux
1. sudo pacman -S git cmake qt5-base
2. git clone https://github.com/ismd/screenshotgun.git
3. cd screenshotgun && mkdir build && cd build
4. cmake ..
5. cmake --build .
#### macOS
1. brew install cmake qt
2. git clone https://github.com/ismd/screenshotgun.git
3. cd screenshotgun && mkdir build && cd build
4. cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt -G Xcode ..
5. Open and build project in Xcode
#### Windows
###### MXE (cross compile for Windows under Linux)
1. Install [MXE](http://mxe.cc/) (need _cmake_ and _qtbase_ packages)
2. git clone https://github.com/ismd/screenshotgun.git
3. cd screenshotgun && mkdir build && cd build
4. x86_64-w64-mingw32.shared-cmake .. -DCMAKE_BUILD_TYPE=Release
5. x86_64-w64-mingw32.shared-cmake --build .

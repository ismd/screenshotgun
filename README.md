# Screenshotgun
Cross-platform open screenshoter with cloud support and server part.  
With this application you can make screenshots, draw different figures or write text on them and then upload to:  
* [screenshotgun.com](http://screenshotgun.com)
* Dropbox
* Google Drive
* Yandex.Disk

Also you can get open source server part and deploy it by yourself [github.com/ismd/screenshotgun-server](https://github.com/ismd/screenshotgun-server)
  
Download binaries for Windows, Linux and macOS from official site [screenshotgun.com](http://screenshotgun.com)   

## Build
### macOS
1. brew install cmake qt
2. git clone https://github.com/ismd/screenshotgun.git
3. mkdir build && cd build
4. CMAKE_PREFIX_PATH=/usr/local/opt/qt cmake -G Xcode ../screenshotgun
5. Open and build project in Xcode

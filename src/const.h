#ifndef CONST_H
#define CONST_H

#define VERSION "1"

#ifndef Q_OS_WIN32
#define TMP_BIN_FILENAME "open-screen-cloud-tmp"
#endif
#ifdef Q_OS_WIN32
#define TMP_BIN_FILENAME "open-screen-cloud-tmp.exe"
#endif

#ifndef Q_OS_WIN32
#define URL_NEW_VERSION  "/dist/open-screen-cloud"
#endif
#ifdef Q_OS_WIN32
#define URL_NEW_VERSION "/dist/open-screen-cloud.exe"
#endif

#endif // CONST_H

#ifndef CONST_H
#define CONST_H

#define VERSION "1"

#ifdef Q_OS_LINUX
#  define TMP_BIN_FILENAME ".screenshotgun-tmp"
#endif

#ifdef Q_OS_WIN32
#  define TMP_BIN_FILENAME "screenshotgun-tmp.exe"
#endif

#ifdef Q_OS_LINUX
#  define URL_NEW_VERSION  "/dist/screenshotgun"
#endif

#ifdef Q_OS_WIN32
#  ifdef Q_OS_WIN64
#    define URL_NEW_VERSION "/dist/screenshotgun-64.exe"
#  else
#    define URL_NEW_VERSION "/dist/screenshotgun.exe"
#  endif
#endif

#endif // CONST_H

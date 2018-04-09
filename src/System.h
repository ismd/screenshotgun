#ifndef SCREENSHOTGUN_SYSTEM_H
#define SCREENSHOTGUN_SYSTEM_H

#include <QLockFile>

class System {

public:
    System();
    ~System();
    bool isLaunched();

private:
    QLockFile lockFile_;
};

#endif // SCREENSHOTGUN_SYSTEM_H

#pragma once

#include <QLockFile>

class System {

public:
    System();
    ~System();

    bool isLaunched();

private:
    QLockFile lockFile_;
};

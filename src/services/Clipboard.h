#pragma once

#include "lib/AbstractService.h"

class Clipboard : public AbstractService {
    Q_OBJECT

public:
    Clipboard();

    void upload(const QImage&);
};

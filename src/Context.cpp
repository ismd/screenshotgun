#include "Context.h"

Context::Context() {
}

Context& Context::getInstance() {
    static Context context;
    return context;
}

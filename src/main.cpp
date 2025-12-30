#include "core/application.h"

int main() {
    lbm::core::Application app;
    if (!app.initialize()) return 1;
    app.run();
    app.shutdown();
    return 0;
}

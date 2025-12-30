#pragma once
#include <iostream>

namespace lbm::utils {

struct Logger {
    template <typename... Args>
    void info(Args&&... args) { (std::cout << ... << args) << std::endl; }
};

}


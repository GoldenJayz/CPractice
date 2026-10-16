#pragma once

#include <string>
#include <chrono>

struct Entry {
    std::string value;
    int expire = NULL;
};

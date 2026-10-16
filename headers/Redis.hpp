#pragma once

#include <unordered_map>
#include <string>

using std::string;

class Redis {
    private:
        std::unordered_map<string, string> keyMap;

    public:
        string getKey(string key) {
            return keyMap[key];
        }

        void setKey(string key, string value) {
            keyMap[key] = value;
        }
};

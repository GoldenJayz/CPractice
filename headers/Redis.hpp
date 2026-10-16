#pragma once

#include <unordered_map>
#include <string>
#include <chrono>
#include "Entry.hpp"

using std::string;
using namespace std::chrono;


class Redis {
    private:
        std::unordered_map<string, Entry> keyMap;

    public:
        Entry getKey(string key) {
            Entry keyObj = keyMap["key"];

            if (keyObj.expire != NULL && keyObj.expire < time_point_cast<seconds>(system_clock::now()).time_since_epoch().count()) {
                keyMap.erase(key); // wipes key if its expired so next call it disappears
            }

            return keyMap[key];
        }

        void setKey(string key, string value) {
            keyMap[key].value = value;
        }

        void setExpire(string key, int expire) {
            expire = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count() + expire;
            keyMap[key].expire = expire;
        }

        int ttl(string key) {
            Entry keyObj = keyMap[key];
            long long now = time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();
            if (keyObj.expire < now) {
                keyMap.erase(key); // wipes key if its expired so next call it disappears

            }
            return keyObj.expire - now; 

        }
};

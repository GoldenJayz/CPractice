#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>
#include "headers/Redis.hpp"

using std::string;
using std::list;
using std::vector;

// check if string can be converted to an integer
bool isInteger(string x) {
    return true;
}

/**
 * @brief Tokenizes the arguments of the user input
 * 
 * Tokens are each one of the arguments for the command
 * which has the action, keyname, and then the value.
 * 
 * @param userPut The user input string
 * @return The tokens sent back in a list
 */
vector<string> tokenize(string userPut) {
    vector<string> actions = {"SET","GET","TTL", "EXIT", "INCR","BEGIN","EXPIRE","ROLLBACK"};
    string temp = "";
    vector<string> retval;
    bool inKeyname = false;
    // this specifically checks the action
    for (int i = 0; i < userPut.length() + 1; i++) {
        int retvalSize = retval.size();
        // go through every character and check if it is GET, SET, INCR, and ...
        char currentChar = userPut[i];
        temp += currentChar; // add the current character to the temp
        // Since the minimum action keyword is 3 letters lock this behind a check for efficiency
        if (i+1 <= 3 && retvalSize == 0) { // since it doesn't get incremented until the end of the run of the current thing
            for (int c = 0; c < actions.size(); c++) {
                if (temp == actions[c]) {
                    retval.push_back(temp);
                    break; // once it finds action break out of the loop
                }
            } // end for 
        } // end if
        // Obtain keyname (2nd argument will always be keyname)
        if (retvalSize == 1) {
            if (currentChar == '\000' || currentChar == ' ') {
                if (inKeyname) {
                    temp.pop_back(); // removes end of line char
                    retval.push_back(temp);
                }
                inKeyname = !inKeyname;
                temp = "";
            }
        }
        // everything after is value
        if (retvalSize == 2) {
            if (currentChar == '\000') {
                retval.push_back(temp);
            }
        }
    } // end for

    return retval;
} // end tokenize



int setKey(string key, string keyValue) {

}


int main() {
    bool isRunning = true;
    Redis redis; // initialize key store system

    // can run a check if the input is an integer or the variable is an integer
    // Need to run a loop where somebody can interact with the data and a way to exit.

    while (isRunning) {
        string userInput = "";
        std::cout << "> ";
        std::getline(std::cin, userInput); // use getline instead of cin

        // Tokenize input perform a string split on the action, on the space
        vector<string> retval = tokenize(userInput);
        string action = retval[0];

        // handle the action corresponding to redis object
        if (action == "GET") {
            string value = redis.getKey(retval[1]);
            std::cout << value << std::endl;
        }
        else if (action == "SET") {
            redis.setKey(retval[1], retval[2]);
            std::cout << redis.getKey(retval[1]) << std::endl;
        }
        else if (action == "EXIT") {
            isRunning = false;
        }
    }
    return 0;
}

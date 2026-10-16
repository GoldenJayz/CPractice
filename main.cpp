#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <iterator>
#include <vector>
#include <headers/Redis.hpp>

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
        if (i+1 >= 3 && retvalSize == 0) { // since it doesn't get incremented until the end of the run of the current thing
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

    std::cout << "hi" << std::endl;
    std::unordered_map<std::string, int> keyMap; // store the 
    // can run a check if the input is an integer or the variable is an integer
    // Need to run a loop where somebody can interact with the data and a way to exit.

    Redis redis;

    while (isRunning) {
        string userInput = "";
        std::cout << "> ";
        std::getline(std::cin, userInput); // use getline instead of cin

        // Tokenize input perform a string split on the action, on the space
        vector<string> retval = tokenize(userInput);

        // debug view tokens
        for (int i = 0; i < retval.size(); i++) {
            std::cout << retval[i] << std::endl;
        }


        //
    }
    return 0;
}

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <iterator>

using std::string;
using std::size;
using std::list;

// check if string can be converted to an integer
bool isInteger(string x) {
    return true;
}


list<string> tokenize(string userPut) {
    string actions[] = {"SET","GET","TTL","INCR","BEGIN","EXPIRE","ROLLBACK"};
    string temp = "";
    list<string> retval;
    bool inKeyname = false;
    // this specifically checks the action
    for (int i = 0; i < userPut.length() + 1; i++) {
        // go through every character and check if it is GET, SET, INCR, and ...
        int listLength = size(retval);
        char currentChar = userPut[i];

        temp += currentChar; // add the current character to the temp
        // Since the minimum action keyword is 3 letters lock this behind a check for efficiency
        if (i+1 >= 3 && retval.size() == 0) { // since it doesn't get incremented until the end of the run of the current thing
            for (int c = 0; c < size(actions); c++) {
                if (temp == actions[c]) {
                    retval.push_back(temp);
                    break; // once it finds action break out of the loop
                }
            } // end for 
        } // end if
        // Obtain keyname
        if (currentChar == '\000' || currentChar == ' ') {
            if (inKeyname) {
                retval.push_back(temp);
            }
            inKeyname = !inKeyname;
            temp = "";
        }


        // if (retval.size() != 0 && currentChar != ' ' && inKeyname == true) {
        //     temp += currentChar;
        // }


        // if (listLength != size(retval)) {
        //     break;
        // }

    } // end for

    return retval;
} // end tokenize

int main() {
    bool isRunning = true;

    std::cout << "hi" << std::endl;
    std::unordered_map<std::string, int> keyMap;
    // can run a check if the input is an integer or the variable is an integer
    // Need to run a loop where somebody can interact with the data and a way to exit.

    while (isRunning) {
        string userInput = "";
        std::cout << "> ";
        std::getline(std::cin, userInput); // use getline instead of cin

        // Tokenize input perform a string split on the action, on the space

        list<string> retval = tokenize(userInput);

        for (int i = 0; i < retval.size(); i++) {
            string output = *std::next(retval.begin(), i);
            std::cout << output << std::endl;
        }
    }

    return 0;
}

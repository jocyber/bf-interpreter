#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <string_view>
#include <cstdlib>

#include "tape.hpp"

int findCorrespondingClosingBrace(const std::string_view programInput, int position);
std::string readFromFile(const std::string&& fileName);

int main(int agrc, char* argv[]) 
{
    const std::string&& programInput = readFromFile(argv[1]);

    Tape tape;
    std::stack<int> openingBraces;

    for (int i = 0; i < programInput.length(); i++) {     
        switch (programInput[i]) {
            case '+': tape.incrementHead(); break;
            case '-': tape.decrementHead(); break;
            case '>': tape.moveRight(); break;
            case '<': tape.moveLeft(); break;
            case '.': std::cout << tape.getHeadData(); break;

            case ',': {
                unsigned char input;
                std::cin >> input;

                tape.setHeadData(input);
            }

            case '[':
                if (tape.getHeadData() == 0) {
                    const int current_position = i;

                    i = findCorrespondingClosingBrace(programInput, current_position);
                }
                else {
                    openingBraces.push(i);
                }

                break;

            case ']':
                if (tape.getHeadData() == 0) {
                    openingBraces.pop();
                }
		else {
                    i = openingBraces.top();
	        }

                break;

            default: break;
        }
    }

    return EXIT_SUCCESS;
}

int findCorrespondingClosingBrace(const std::string_view programInput, int openBracePosition) {
    std::stack<char> st;

    for (int i = openBracePosition + 1; i < programInput.length(); i++) {
        switch (programInput[i]) {
            case '[': st.push('['); break;

            case ']':
                if (st.empty()) {
                    return i;
                }

                st.pop();
                break;

            default: break;
        }   
    }

    //throw an error
    return -1;
}

std::string readFromFile(const std::string&& fileName) {
    std::ifstream file(fileName, std::ios::in);
    std::stringstream ss;

    if (file.is_open()) {
        ss << file.rdbuf();
    }

    file.close();
    return ss.str();
}

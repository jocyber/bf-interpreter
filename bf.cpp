#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <string_view>
#include <cstdlib>

int findCorrespondingClosingBrace(const std::string_view programInput, int position);
std::string readFromFile(const std::string&& fileName);

int main(int agrc, char* argv[]) 
{
    using Tape = std::vector<char>;

    const std::string&& programInput = readFromFile(argv[1]);

    Tape tape(30000, 0);

    int programCounter = 15000;
    std::stack<int> openingBraces;

    for (int i = 0; i < programInput.length(); i++) {     
        switch (programInput[i]) {
            case '+': tape[programCounter]++; break;
            case '-': tape[programCounter]--; break;

            case '>':
                if (programCounter == tape.size() - 1) {
                    tape.push_back(0);
                }

                programCounter++;
                break;

            case '<':
                if (programCounter == 0) {
                    tape.insert(tape.begin(), 0);
		    //tape.push_front(0);
                    break;
                }

                programCounter--; 
                break;

            case '.': std::cout << tape[programCounter]; break;

            case '[':
                if (tape[programCounter] == 0) {
                    const int current_position = i;

                    i = findCorrespondingClosingBrace(programInput, current_position);
                }
                else {
                    openingBraces.push(i);
                }

                break;

            case ']':
                if (tape[programCounter] == 0) {
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

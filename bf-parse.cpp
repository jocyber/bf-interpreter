#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <sstream>

int findCorrespondingClosingBrace(const std::string& programInput, int position);
std::string readFromFile(const std::string&& fileName);

int main(int agrc, char* argv[]) 
{
    //using Tape = std::deque<char>;
		using Tape = std::vector<char>;

    const std::string programInput = readFromFile("mandelbrot.bf");

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

                    if (i == -1) {
                        std::cerr << "No matching brace for [ at position " << current_position << '\n';
                        exit(1);
                    }
                }
                else {
                    openingBraces.push(i);
                }

                break;

            case ']':
                if (openingBraces.empty()) {
                    std::cerr << "No opening brace for ] at position " << i << '\n';
                    exit(1);
                }

                if (tape[programCounter] == 0) {
                    openingBraces.pop();
                    break;
                }

                i = openingBraces.top() - 1;
                openingBraces.pop();

                break;

            default: break;
        }
    }

    return 0;
}

int findCorrespondingClosingBrace(const std::string& programInput, int position) {
    std::stack<char> st;

    for (int i = position + 1; i < programInput.length(); i++) {
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

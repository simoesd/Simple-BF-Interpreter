#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Interpreter.cpp"

//"+" and "-": increment and decrement currently selected byte
//">" and "<": move pointer to the left or right one byte
//"." and ",": output or receive input for the current byte to and from standard output/input
//"[" and "]": define the start and end of a cycle block. Skip the block if the current byte is 0 at the start


int main(int argc, char **argv) {
    std::cout << "Compiling and executing code" << std::endl;

    std::string filepath = argv[1]; //TODO get filepath from command line
    std::ifstream t(filepath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string program = buffer.str();
//    std::string program = "+.,.>++.,.>+++.,.>++++.,.<<<-.,.>--.,.>---.,.>----.,.";

    Interpreter *interpreter = new Interpreter(program);
    return interpreter->run();
}



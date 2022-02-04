//
// Created by David on 04-Feb-22.
//
#include <iostream>
#include "string"

class Interpreter {
    std::string program;
    unsigned char array[30000] = "\0";
    int pointer = 0;

    public: Interpreter(std::string program)
    {
        this->program = program;
        parseCode();
    }

    public: int parseCode()
    {
        int i = 0;
        while (i < program.length()) {
            switch (program[i]) {
                case '+':
                    array[pointer]++; //TODO define increment behavior above 255
                    break;
                case '-':
                    array[pointer]--; //TODO define decrement behavior above 255
                    break;
                case '>':
                    pointer++; //TODO define pointer behavior above array length (error or looping perhaps)
                    break;
                case '<':
                    pointer--; //TODO define pointer behavior below 0 (error or looping perhaps)
                    break;
                case '.':
                    std::cout << array[pointer] + 0x0; //TODO print in the same line, even after io flush
                    break;
                case ',':
                    unsigned char buffer; //TODO define behavior when input is outside the ASCII table or multiple characters were input at once
                    std::cin >> buffer;
                    array[pointer] = buffer - 0x0;
                    break;
                case '[':
                    break; //TODO pending implementation
                case ']':
                    break; //TODO pending implementation
                default:
                    //Beyond the instruction characters everything is treated as a comment, and thus nothing is executed
                    break;
            }
            i++;
        }
    }
};

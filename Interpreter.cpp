#include "iostream"
#include "utility"
#include "string"
#include "limits"
#include "vector"

class Interpreter {
    std::string program;
    int pointer = 0;
    std::vector<unsigned char> array = std::vector<unsigned char>(30000);
    int errorAtInstruction = 0;

    public: explicit Interpreter(std::string program)
    {
        this->program = std::move(program);
    }

    public: int run() {
        int bracketCode = checksumBrackets();
        if (bracketCode > 0) {
            std::cout << "Interpretation Exception: Invalid bracket structure. Perhaps you forgot to close a loop? (Instruction ["
                << errorAtInstruction << "])." << std::endl;
            return -1;
        } else if (bracketCode) {
            std::cout << "Interpretation Exception: Invalid bracket structure. Perhaps you forgot to open a loop? (Instruction ["
                << errorAtInstruction << "])." << std::endl;
            return -1;
        }
        return parseCode();
    }

    //Counts the number of brackets in the program. Open brackets increase the sum, while closed brackets decrease it.
    //If at any point the sum drops below zero, a loop was closed before it was opened and as such the program is not
    //valid.
    //If at the end of the program the sum is greater than zero, a loop was opened and never closed, and thus the
    //program is not valid.
    int checksumBrackets() {
        int i = 0;
        int sum = 0;
        while (i < program.length() && sum >= 0) {
            switch (program[i]) {
                case '[':
                    sum++;
                    break;
                case ']':
                    sum--;
                    break;
                default:
                    break;
            }
            i++;
        }
        errorAtInstruction = i;
        return sum;
    }

    public: int parseCode()
    {
        int i = 0;
        while (i < program.length()) {
            switch (program[i]) {
                case '+':
                    //If the element at the pointer is already at the max value an error is displayed
                    if (array[pointer] == 255) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Value incremented above 255. (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    array[pointer]++;
                    break;
                case '-':
                    //If the element at the pointer is already at the minimum value an error is displayed
                    if (!array[pointer]) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Value decremented below 0. (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    array[pointer]--;
                    break;
                case '>':
                    pointer++;
                    //If the pointer is moved beyond the upper bound of the array, the array is extended
                    if (pointer == array.size())
                        array.resize(array.size()*2);
                    break;
                case '<':
                    //If the pointer is at the left most position an error is displayed
                    if (!pointer) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Pointer moved out of bounds (below zero). (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    pointer--;
                    break;
                case '.':
                    std::cout << array[pointer];
                    break;
                case ',':
                    unsigned char buffer;
                    std::cin >> buffer;
                    //If the read value is outside the bounds of 1 byte and error is displayed
                    if (buffer < 0 || buffer > 255){
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Read value must be part of the ASCII table. (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    array[pointer] = buffer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    break;
                case '[':
                    //If the element at the pointer is not zero the end of the current loop must be found.
                    //Since loops can be nested, whenever another loop is opened we increment the "layer" counter.
                    //Whenever a loop is closed, this counter is decremented.
                    //If the counter reaches zero we have found the end of our loop, and execution is resumed there.
                    if (!array[pointer]) {
                        int layer = 1;
                        while (layer += (program[++i] == '[' ? 1 : (program[i] == ']' ? -1 : 0)));
                    }
                    break;
                case ']':
                    //If the element at the pointer is zero the beginning of the current loop must be found to be repeated.
                    //Since loops can be nested, whenever another loop is closed we increment the "layer" counter.
                    //Whenever a loop is opened, this counter is decremented.
                    //If the counter reaches zero we have found the beginning of our loop, and execution is resumed there.
                    if (array[pointer]) {
                        int layer = 1;
                        while (layer += (program[--i] == '[' ? -1 : (program[i] == ']' ? 1 : 0)));
                    }
                    break;
                default:
                    //Beyond the instruction characters everything is treated as a comment, and thus nothing is executed
                    break;
            }
            i++;
        }
        return 0;
    }
};

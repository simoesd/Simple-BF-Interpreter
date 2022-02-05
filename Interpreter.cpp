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
                    if (array[pointer] == 255) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Value incremented above 255. (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    array[pointer]++;
                    break;
                case '-':
                    if (!array[pointer]) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Value decremented below 0. (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    array[pointer]--;
                    break;
                case '>':
                    if (pointer > array.size())
                        array.resize(array.size()*2);
                    pointer++;
                    break;
                case '<':
                    if (!pointer) {
                        errorAtInstruction = i + 1;
                        std::cout << "Execution exception: Pointer moved out of bounds (below zero). (Instruction ["
                                  << errorAtInstruction << "])." << std::endl;
                        return -1;
                    }
                    pointer--;
                    break;
                case '.':
                    std::cout << array[pointer]; //TODO print in the same line, even after io flush
                    break;
                case ',':
                    unsigned char buffer;
                    std::cin >> buffer;
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
                    if (!array[pointer]) {
                        int layer = 1;
                        while (layer += (program[++i] == '[' ? 1 : (program[i] == ']' ? -1 : 0)));
                    }
                    break;
                case ']':
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

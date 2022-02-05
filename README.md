# Brainfuck Interpreter

This is a very simple and primitive Brainfuck Interpreter that was put together as a first experience with C++. It receives the path to your Brainfuck file as an argument and will then attempt to interpret and execute it while providing (very limited) information in case a problem with the program is found.

Brainfuck is an esoteric language where you directly access an array utilizing a pointer to a position in this array. It contains only 8 commands:
 - "+" and "-": Increment or decrement the element of the array the pointer is currently pointing to;
 - ">" and "<": Move the pointer one element to the right or left, respectively;
 - "," and ".": Read one character from standard input and overwrite the element the pointer is currently at with the read character, or output this element to standard output.
 - "\[" and "\]": Marks the beginning and end of a cycle block. When a "\[" command is reached, if the current element's value is 0 the execution will skip to the corresponding "\]" command. When a "\]" command is reached, if the current element's value is *not* 0 the execution will skip to the corresponding "\[" command.

As Brainfuck does not have a very strong specification, certain design and implementation decisions were taken:
 - The data array is composed of 1 byte characters;
 - The data array is initialized with 30000 elements, but this size is doubled whenever the pointer attempts to move outside the upper bound. Array extension is not made when the pointer attemps to move below the lower bound, and the array size is never reduced after an extension. Elements are initialized as 0;
 - Attempting to increment or decrement an element outside the 1 byte range (0-255) will cause an exception and the program will be aborted. Inputting a character whose value is outside this range will result in an exception and the program to abort as well;
 - If more than one character is input during a "," command, only the first character will be read, and the rest will be discarded;
 - Before the program is executed, a preliminar check is ran that verifies if there is no unnopened or unclosed cycle;
 - Loops can be nested;
 - Every character in the file to be executed that does not belong to the command set is ignored and treated as a comment.
 
 If the interpreter runs into a problem when verifying or executing your program, an error message will be shown with the instruction number where the problem was identified. These include two Interpretation Excetions (every "\[" should have a matching "\]"):
 - "Interpretation Exception: Invalid bracket structure. Perhaps you forgot to close a loop? (Instruction \[x\])" - You are not closing all the loops you opened. The instruction number shown is always at the end of the program;
 - "Interpretation Exception: Invalid bracket structure. Perhaps you forgot to open a loop? (Instruction \[x\])" - You are closing a loop when there isn't any open loop. The instruction number shown will correspond to the "\]".

 There are also four Execution Exceptions, where the instruction number provided corresponds to where in the program the execution was aborted:
 -  "Execution exception: Value incremented above 255. (Instruction \[x\])";
 -  "Execution exception: Value decremented below 0. (Instruction \[x\])";
 -  "Execution exception: Pointer moved out of bounds (below zero). (Instruction \[x\])";
 -  "Execution exception: Read value must be part of the ASCII table. (Instruction \[x\])".

I might come back to this project and try to put together a simple text editor/IDE GUI, making the interpreter be usable outside the command line but my initial goals for the project have been completed.

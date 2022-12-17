#include "cpu.h"

int main()
{

    FILE * asmcode = NULL;
    int registers[AMOUNT_OF_REGISTERS] = {1, 2};
    int ram[10] = {1, 2, 3, 4, 5, 6};
    stack_type stack = {};
    stackCreator_(&stack, 5);
    ReadAsm(asmcode, &stack, registers, ram);
    return 0;
}

//==============================================================================


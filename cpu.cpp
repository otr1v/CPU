#include "cpu.h"
#include "funccpu.h"


int main()
{
    CPU cpu = {};
    FILE * asmcode = NULL;
    cpu.registers[0] = 1;
    cpu.registers[1] = 2;
    //TODO create RAM, create regs
    int ram[10] = {1, 2, 3, 4, 5, 6};
    stack_type stack = {};
    stackCreator_(&(cpu.stack), 5);
    elem_t d = 5;
    stackPush(&(cpu.stack), &d);
    ReadAsm(asmcode, &cpu);
    return 0;
}

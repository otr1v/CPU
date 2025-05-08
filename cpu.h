#ifndef CPU_HEADER
#define CPU_HEADER
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "stack/func.cpp"
#include <math.h>
#include "enum.h"


typedef struct 
{
    stack_type stack;
    int registers[AMOUNT_OF_REGISTERS];
    int ram[NUMBER_OF_RAM_ELEMS];
    int* code;
}CPU;

void CreateCpu(CPU* cpu);
int ReadAsm(FILE * asmcode, CPU* cpu);
int GetArgs(int* ip, CPU* cpu);
int MySqrt(int a);

#endif


#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "enum.h"


const int MAX_LABEL_SIZE      = 300;
const int MAX_COMMANDS        = 1000;
const int MASK_IMMED          = 1 << 6;
const int MASK_REGISTER       = 1 << 7;
const int MASK_RAM            = 1 << 8;
const int AMOUNT_OF_RAM       = 15;
const int MAX_NAME_REG_SIZE   = 6;
const int MAX_SIZE_OF_COMMAND = 10;


typedef struct 
{
    int labels[MAX_LABEL_SIZE];
    int code[MAX_COMMANDS];
    char** text;
    int read_symbols;
    int current_line;
}ASM;

void CreateAsm(ASM* asmstruct);
int* ReadFile(ASM* asmstruct, char* filename);
int CounterStrings(int size_buf, char* buf);
int* WriteCommands(ASM* asmstruct, int num_of_commands);
void ClearArray(int code[]);
int ReadArgs(ASM* asmstruct, char cmd[], int* ip);


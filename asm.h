#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)
// #define DEF_CMD(name, num, arg) \
//         CMD_##name = num,
// enum 
// {
//     #include "cmd.h"
// }
// #undef DEF_CMD

// #define DEF_CMD(name, num, arg) \
//             if (strcmp(cmd, #name) == 0) \
//                 {code[ip++] = num;   \
//                 if (arg) GetArgs();}   \
//                 else

;

const int MAX_LABEL_SIZE      = 300;
const int MAX_COMMANDS        = 1000;
const int AMOUNT_OF_REGISTERS = 20;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int REG_REX             = 4;
const int REG_RFX             = 5;
const int MASK_IMMED          = 1 << 6;
const int MASK_REGISTER       = 1 << 7;
const int MASK_RAM            = 1 << 8;
const int AMOUNT_OF_RAM       = 15;
const int MAX_NAME_REG_SIZE   = 6;
const int MAX_SIZE_OF_COMMAND = 10;
enum 
{
    CMD_PUSH = 1,
    CMD_POP  = 2,
    CMD_ADD  = 3,
    CMD_SUB  = 4,
    CMD_MUL  = 5,
    CMD_DIV  = 6,
    CMD_OUT  = 7,
    CMD_IN   = 8,
    CMD_HLT  = 9,
    CMD_JMP  = 10,
    CMD_SQRT = 11,
    CMD_CPY  = 12,
    CMD_JB   = 13,
    CMD_JE   = 14,
    CMD_CALL = 15,
    CMD_FACT = 16,
    NO_MEMORY,
    ERR_OPEN_FILE, 
    BAD_FREAD
};

int* ReadFile(int code[], int labels[]);
int CounterStrings(FILE* fp, int size_buf, char* buf);
int* WriteCommands(int code[], int num_of_commands, char** text, int labels[]);
void ClearArray(int code[]);
int ReadArgs(int code[], char** text, char cmd[], int read_symbols, int current_line, int* ip);



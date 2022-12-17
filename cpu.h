#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../stack/func.cpp"
#include <math.h>

int ReadAsm(FILE * asmcode, stack_type* stk, int registers[], int ram[]);
int FileSize(FILE* fp);
int GetArgs(int code[], int registers[], int ram[], int* ip);
int MySqrt(int a);

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)

const int ARG_IMMED           = 1 << 5;
const int ARG_REG             = 1 << 6;
const int ARG_RAM             = 1 << 7;
const int AMOUNT_OF_REGISTERS = 20;
const int CMD_MASK            = 0xF;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int REG_REX             = 4;
const int REG_RFX             = 5;
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
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

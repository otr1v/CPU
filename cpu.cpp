#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../stack/func.cpp"

void ReadAsm(FILE * asmcode, stack_type* stk, int registers[], int ram[]);
int FileSize(FILE* fp);
int GetArgs(int code[], int registers[], int ram[], int* ip);


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
    CMD_POW2 = 12,
    CMD_CPY  = 13,
    CMD_JA   = 14,
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

int main()
{

    FILE * asmcode = NULL;
    printf("kl");
    int registers[AMOUNT_OF_REGISTERS] = {1, 2};
    int ram[10] = {1, 2, 3, 4, 5, 6};
    stack_type stack = {};
    stackCreator_(&stack, 5);
    ReadAsm(asmcode, &stack, registers, ram);
    return 0;
}

//==============================================================================

void ReadAsm(FILE * asmcode, stack_type* stk, int regs[], int ram[])
{
    int* err = {};
    elem_t pop_value     = POISON;
    elem_t cmd_pop_value = POISON;
    asmcode = fopen("out.bin", "rb");
    if (asmcode == NULL)
    {
        printf("nild");
    }
    int size_buf = FileSize(asmcode);
    int* code = (int *) calloc((size_buf / sizeof(int)) + 1, sizeof(int));
    printf("any");
    int res = fread(code, sizeof(int), size_buf, asmcode);
    printf("%d", res);
    fclose(asmcode);

    //printf("%d", res);
    for (int i = 0; i < (size_buf / sizeof(int)); i++)
    {
        printf("%d\n", code[i]);
        printf("lolll");
        printf("i %d\n", i);
    }
    //printf("how");

    int ip = 0;
    int val = 0;
    int cmd = 0;
   // printf("%ld\n", size_buf / sizeof(int));
    while(ip !=  ((size_buf / sizeof(int)) ))
    {
        // printf("%d\n", ip);
        // printf("In stack %d\n", stk->data[stk->size - 1]);
        //printf("ip%d", ip);

        switch (code[ip] & CMD_MASK)
        {
        case CMD_PUSH:
           // printf("ip");
            val = GetArgs(code, regs, ram, &ip);
            printf("push value is %d\n", val);
            stackPush(stk, &val);
            //printf("code : %d\n", stk->data[stk->size - 1]);
            //ip += 2;
            break;
        case CMD_ADD:
            // printf("In stack %d\n", stk->data[stk->size]);
            //stackPop(stk, err, &pop_value1);
            // printf("In stack %d\n", stk->data[stk->size]);
            //stackPop(stk, err, &pop_value2);
            // printf("pop value1 = %d\n", pop_value1);
            // printf("pop value2 = %d\n", pop_value2);
            pop_value = stackPop(stk, err) + stackPop(stk, err);
            //printf("pop value = %d\n", pop_value);
            stackPush(stk, &pop_value);
            ip++;
            break;
        case CMD_DIV:
            ip++;
            break;
        case CMD_POP:
            ip++;
            cmd_pop_value = stackPop(stk, err);
            printf("code[ip]%d\n", code[ip]);
            regs[code[ip++]] = cmd_pop_value;
            break;
        case CMD_HLT:
            ip++;
            break;
        case CMD_JMP:
            ip++;
            printf("ipiii%d", ip);
            ip = code[ip];
            printf("look%d", ip);
            break;
        case CMD_SQRT:
            pop_value = stackPop(stk, err);
            if (pop_value < 0)
            {
                printf("sqrt of number that < 0");
            }
            else 
            {

            }
            ip++;
            break;
        case CMD_CPY:
            pop_value = stackPop(stk, err);
            stackPush(stk, &pop_value);
            stackPush(stk, &pop_value);
            ip++;
            break;
        case CMD_MUL:
            pop_value = (stackPop(stk, err)) * (stackPop(stk, err));
            printf("whatlol");
            stackPush(stk, &pop_value);
            printf("%d\n", stk->data[stk->size - 1]);
            ip++;
            break;
        case CMD_JA:
            if (stk->data[stk->size - 1] > 10)
            {
                ip += 2;
            }
            else
            {
                ip++;
                ip = code[ip];
            }
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        printf("%d.%d\n", i, stk->data[i]);
        printf("regs %d\n", regs[i]);
    }
    //printf("stack");
}

//=================================================================================

int FileSize(FILE* fp)
{
    struct stat buffer = {};
    int res_fstat = fstat(fileno(fp), &buffer);
    CHECK_ERR(res_fstat == -1, "can't fill the structure stat", ERR_FSTAT);
    int size_buf = buffer.st_size;
    return size_buf;
}

//=====================================================================================

int GetArgs(int code[], int regs[], int ram[], int* ip)
{
    int cmd = code[(*(ip))++];
    int arg = 0;
    //printf("lol");
    if (cmd & ARG_IMMED)
    {
        arg = code[(*(ip))++];
    }
    if (cmd & ARG_REG)
    {
        arg = regs[code[(*(ip))++]];
    }
    if (cmd & ARG_RAM)
    {
        arg = ram[arg];
    }
    printf("arg%d\n", arg);
    return arg;
}

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../stack/func.cpp"
#include <math.h>

void ReadAsm(FILE * asmcode, stack_type* stk, int registers[], int ram[]);
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
    CMD_POW2 = 12,
    CMD_CPY  = 13,
    CMD_JB   = 14,
    CMD_JE  = 15,
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

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
    int res = fread(code, sizeof(int), size_buf, asmcode);
    fclose(asmcode);
    FILE* dump = fopen("dump.txt", "w");
    //printf("%d", res);
    for (int i = 0; i < (size_buf / sizeof(int)); i++)
    {
        printf("%d\n", code[i]);
        //printf("lolll");
        //printf("i %d\n", i);
    }
    //printf("how");

    int ip = 0;
    int val = 0;
    int cmd = 0;
    int first_pop = 0, second_pop = 0, sub_result = 0, div_result = 0, sqrt_result = 0;
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
            printf( "addval %d\n", stk->data[stk->size - 1]);

            ip++;
            break;
        case CMD_DIV:
            if (stk->data[stk->size - 1] != 0)
            {
                first_pop = stackPop(stk, err);
                second_pop = stackPop(stk, err);
                div_result = (int)(second_pop / first_pop);
                stackPush(stk, &div_result);
            }
            else
            {
                printf("attempt to divide by 0\n");
            }
            printf("divvvv %d", div_result);
            ip++;
            break;
        case CMD_POP:
            ip++;
            cmd_pop_value = stackPop(stk, err);
            printf("code[ip]%d\n", code[ip]);
            regs[code[ip++]] = cmd_pop_value;
            printf("reg %d", regs[3]);
            break;
        case CMD_HLT:
            if (regs[REG_REX] == 0)
            {
                printf("no roots\n");
            }
            else
            {
                printf("the first root %d\n the second root %d\n", regs[REG_REX], regs[REG_RFX]);
            }
            exit(1);
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
                //sqrt_result = MySqrt(pop_value);
                sqrt_result = (int)(pop_value / 2);
                stackPush(stk, &sqrt_result);
            }
            ip++;
            break;
        case CMD_CPY:
            pop_value = stackPop(stk, err);
            stackPush(stk, &pop_value);
            stackPush(stk, &pop_value);
            printf("CPY ARG%d and %d\n", stk->data[stk->size - 1], stk->data[stk->size - 2]);
            ip++;
            break;
        case CMD_MUL:
            pop_value = (stackPop(stk, err)) * (stackPop(stk, err));
            printf("whatlol");
            stackPush(stk, &pop_value);
            printf("mulval %d\n", stk->data[stk->size - 1]);
            printf("rex %d\n", regs[REG_REX]);
            ip++;
            break;
        case CMD_JB:
            if (regs[REG_RDX] > 0)
            {
                ip++;
                ip = code[ip] + 1;
                printf("ipp %d", ip);
            }
            else
            {
                ip += 2;
            }
            break;
        case CMD_JE:
            if (regs[REG_RDX] == 0)
                {
                    ip++;
                    ip = code[ip] - 1;
                }
            else
            {
                ip += 2;
            }
            break;
        case CMD_SUB:
            first_pop = stackPop(stk, err);
            second_pop = stackPop(stk, err);
            sub_result = second_pop - first_pop;
            stackPush(stk, &sub_result);
            printf("sub res %d\n", sub_result);
            ip++;
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

//========================================================================

int MySqrt(int a)
{
    double num = (double) a;
    double res =  sqrt(1);
    int result = (int) res;
    return result;
}

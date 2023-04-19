#include "cpu.h"
#include "filesize.cpp"
#define QUADRO_EQ

void CreateCpu(CPU* cpu)
{
    for (int i = 0; i < AMOUNT_OF_REGISTERS; i++)
    {
        cpu->registers[i] = 0;      // some expressions to fill by your own
    }                                   // all about RAM and registers
    for (int j = 0; j < NUMBER_OF_RAM_ELEMS; j++)
    {
        cpu->ram[j] = j + 1;        // filling elements of ram and registers are random
    }
    cpu->code = NULL;
    cpu->stack = {};
}

//==========================================================

int ReadAsm(FILE * asmcode, CPU* cpu)
{
    int* err = {};
    elem_t pop_value     = POISON;
    elem_t cmd_pop_value = POISON;
    
    asmcode = fopen("out.bin", "rb");
    CHECK_ERR(asmcode == NULL, "can't open file", ERR_OPEN_FILE);
    
    int size_buf = FileSize(asmcode);
    cpu->code = (int *) calloc((size_buf / sizeof(int)) + 1, sizeof(int));
    int res = fread(cpu->code, sizeof(int), size_buf, asmcode);
    fclose(asmcode);
    
    int counter = 0, insidecounter = 0;
    int ip = 0;
    int val = 0;
    int first_pop = 0, second_pop = 0, sub_result = 0, div_result = 0, sqrt_result = 0;

    while(ip !=  ((size_buf / sizeof(int)) ))
    {
       
        switch (cpu->code[ip] & CMD_MASK){
        
        #define DEF_CMD(name, num, arg, code)   \
            case num:                            \
                code printf("one") ;                            \
                ip++;                              \
                break;
        #define DEF_JMP(name, num, symbol)       \
            case num:                                  \
                first_pop  = stackPop(&cpu->stack, err);\
                second_pop = stackPop(&cpu->stack, err); \
                if (second_pop symbol first_pop)          \
                {                                          \
                    ip++;                                   \
                    ip = cpu->code[ip] - 1;                  \ 
                }                                               \
                else                                            \
                {                                               \   
                    ip+=2;                                         \
                }                                         \
                break; 

        #include "cmd.h"              
        default:
            break;
        #undef DEF_JMP
        #undef DEF_CMD
        }        
    }
    
    free(cpu->code);
    return 0;
}


//=====================================================================================

int GetArgs(int* ip, CPU* cpu)
{
    int cmd = cpu->code[(*(ip))++];
    int arg = 0;
    
    if (cmd & ARG_IMMED)
    {
        arg = cpu->code[(*(ip))];
    }
    if (cmd & ARG_REG)
    {
        if (cmd & CMD_PUSH)
        {
            arg = cpu->registers[cpu->code[(*(ip))]];
        }
        else
        {
            arg = cpu->code[(*(ip))];
        }
    }
    if (cmd & ARG_RAM)
    {
        arg = cpu->ram[arg];
    }
    return arg;
}

//========================================================================

int MySqrt(int a)
{
    int res =  (int)sqrt(a);
    return res;
}

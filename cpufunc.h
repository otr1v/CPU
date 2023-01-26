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
    //printf("%d", res);
    for (int i = 0; i < (size_buf / sizeof(int)); i++)
    {
        printf("%d. %d\n", i, cpu->code[i]);
        //printf("lolll");
        //printf("i %d\n", i);
    }
    //printf("how");
    int counter = 0, insidecounter = 0;
    int ip = 0;
    int val = 0;
    int first_pop = 0, second_pop = 0, sub_result = 0, div_result = 0, sqrt_result = 0;
   // printf("%ld\n", size_buf / sizeof(int));
    while(ip !=  ((size_buf / sizeof(int)) ))
    {
        // printf("%d\n", ip);
        // printf("In stack %d\n", cpu->stack->data[cpu->stack->size - 1]);
        //printf("ip%d", ip);
                //printf("cnsdc");

        switch (cpu->code[ip] & CMD_MASK){
        // {
        // case CMD_PUSH:
        //    // printf("ip");
        //     val = GetArgs(&ip, cpu);
        //     printf("push value is %d\n", val);
        //     printf("hf");
        //     stackPush(&(cpu->stack), &val);
        //     printf("hf");

        //     //printf("code : %d\n", cpu->stack->data[cpu->stack->size - 1]);
        //     //ip += 2;
        //     break;
        // case CMD_ADD:
        //     // printf("In stack %d\n", cpu->stack->data[cpu->stack->size]);
        //     //stackPop(cpu->stack, err, &pop_value1);
        //     // printf("In stack %d\n", cpu->stack->data[cpu->stack->size]);
        //     //stackPop(cpu->stack, err, &pop_value2);
        //     // printf("pop value1 = %d\n", pop_value1);
        //     // printf("pop value2 = %d\n", pop_value2);
        //     // printf("hf");

        //     pop_value = stackPop(&cpu->stack, err) + stackPop(&cpu->stack, err);
        //     //printf("pop value = %d\n", pop_value);
        //     stackPush(&cpu->stack, &pop_value);
        //     //printf( "addval %d\n", (cpu->stack.data[cpu->stack.size - 1]));

        //     ip++;
        //     break;
        // case CMD_DIV:
        //     if (cpu->stack.data[cpu->stack.size - 1] != 0)
        //     {
        //         first_pop = stackPop(&cpu->stack, err);
        //         second_pop = stackPop(&cpu->stack, err);
        //         div_result = (int)(second_pop / first_pop);
        //         stackPush(&cpu->stack, &div_result);
        //     }
        //     else
        //     {
        //         printf("attempt to divide by 0\n");
        //     }
        //     printf("divvvv %d", div_result);
        //     ip++;
        //     break;
        // case CMD_POP:
        //     //ip++;
        //     cmd_pop_value = stackPop(&(cpu->stack), err);
        //     val = GetArgs(&ip, cpu);
        //     cpu->registers[val] = cmd_pop_value;
        //     printf("reg %d", cpu->registers[3]);
        //     break;
        // case CMD_HLT:
        //     #ifdef QUADRO_EQ
        //         if (cpu->registers[REG_REX] == 0)
        //         {
        //             printf("no roots\n");
        //         }
        //         else
        //         {
        //             printf("the first root %d\n the second root %d\n", cpu->registers[REG_REX], cpu->registers[REG_RFX]);
        //         }
        //     #endif
        //     return 0;
        //     break;
        // case CMD_JMP:
        //     ip++;
        //     printf("ipiii%d", ip);
        //     ip = cpu->code[ip];
        //     printf("look%d", ip);
        //     break;
        // case CMD_SQRT:
        //     pop_value = stackPop(&cpu->stack, err);
        //     if (pop_value < 0)
        //     {
        //         printf("sqrt of number that < 0");
        //     }
        //     else 
        //     {
        //         sqrt_result = MySqrt(pop_value);
        //         stackPush(&cpu->stack, &sqrt_result);
        //     }
            
        //     ip++;
        //     break;
        // case CMD_CPY:
        //     pop_value = stackPop(&cpu->stack, err);
        //     stackPush(&cpu->stack, &pop_value);
        //     stackPush(&cpu->stack, &pop_value);
        //     //printf("CPY ARG%d and %d\n", cpu->stack.data[cpu->stack.size - 1], cpu->stack.data[cpu->stack.size - 2]);
        //     ip++;
        //     break;
        // case CMD_MUL:
        //     pop_value = (stackPop(&cpu->stack, err)) * (stackPop(&cpu->stack, err));
        //     stackPush(&cpu->stack, &pop_value);
        //     // printf("mulval %d\n", cpu->stack.data[cpu->stack.size - 1]);
        //     // printf("rex %d\n", cpu->registers[REG_REX]);
        //     ip++;
        //     break;
        // case CMD_JB:
        //     if (cpu->registers[REG_RDX] > 0)
        //     {
        //         ip++;
        //         ip = cpu->code[ip] + 1;
        //         printf("ipp %d", ip);
        //     }
        //     else
        //     {
        //         ip += 2;
        //     }
        //     break;
        // case CMD_JE:
        //     #ifdef QUADRO_EQ
        //         ip++;
        //         // if (cpu->registers[REG_RAX] == 0)
        //         // {
        //         //     ip = cpu->code[ip] - 1;
        //         // }
        //         if (counter == 1)
        //         {
        //             if (cpu->registers[REG_RDX] == 0)
        //                 {
                            
        //                     ip = cpu->code[ip] - 1;
        //                 }
        //             else
        //             {
        //                 ip++;
        //             }
        //             counter++;
        //         }
        //         else if (counter == 0)
        //         {
        //             if ((cpu->registers[REG_RAX] == 0) && 
        //                 (cpu->registers[REG_RBX] == 0) &&
        //                 (cpu->registers[REG_RCX] == 0))
        //                 {
        //                     printf("infinity roots");
        //                     ip = cpu->code[ip] - 1;
        //                     insidecounter++;
        //                 }
        //             else if((cpu->registers[REG_RAX] == 0) && 
        //                 (cpu->registers[REG_RBX] == 0) &&
        //                 (cpu->registers[REG_RCX] != 0))
        //                 {
        //                     printf("no roots");
        //                 }
        //             else if((cpu->registers[REG_RAX] == 0) && 
        //                 (cpu->registers[REG_RBX] != 0) &&
        //                 (cpu->registers[REG_RCX] != 0))
        //                 {
        //                     ip = cpu->code[ip] - 1;
        //                 }
        //             else if ((cpu->registers[REG_RAX] != 0) && (insidecounter == 0))
        //             {
        //                 ip++;
        //                 counter++;
        //             }
        //             else
        //             {

        //             }
                    
        //         }
        //     #endif
        //     break;
        // case CMD_SUB:
        //     first_pop = stackPop(&cpu->stack, err);
        //     second_pop = stackPop(&cpu->stack, err);
        //     sub_result = second_pop - first_pop;
        //     stackPush(&cpu->stack, &sub_result);
        //     printf("sub res %d\n", sub_result);
        //     ip++;
        //     break;
        // default:
        //     break;
        // }
        #define DEF_CMD(name, num, arg, code)   \
            case num:                            \
                code                              \
                ip++;                              \
                break;
        #include "cmd.h"
        default:
            break;
        #undef DEF_CMD
        }        
    }
    for (int i = 0; i < 7; i++)
    {
        printf("cnsdc");
        printf("%d.%d\n", i, cpu->stack.data[i]);
        printf("cpu->registers %d\n", cpu->registers[i]);
    }
    free(cpu->code);
    return 0;
    //printf("stack");
}


//=====================================================================================

int GetArgs(int* ip, CPU* cpu)
{
    int cmd = cpu->code[(*(ip))++];
    int arg = 0;
    //printf("lol");
    if (cmd & ARG_IMMED)
    {
        arg = cpu->code[(*(ip))];
    }
    if (cmd & ARG_REG)
    {
        arg = cpu->registers[cpu->code[(*(ip))]];
    }
    if (cmd & ARG_RAM)
    {
        arg = cpu->ram[arg];
    }
    printf("arg%d\n", arg);
    return arg;
}

//========================================================================

int MySqrt(int a)
{
    int res =  (int)sqrt(a);
    return res;
}

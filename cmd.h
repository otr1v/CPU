DEF_CMD (PUSH,  1, 1, 
    {
        val = GetArgs(&ip, cpu);
        stackPush(&(cpu->stack), &val);
    }
)
DEF_CMD (POP,   2, 1, 
    {
        cmd_pop_value = stackPop(&(cpu->stack), err);
        val = GetArgs(&ip, cpu);
        cpu->registers[val] = cmd_pop_value;
    }
)
DEF_CMD (ADD,   3, 0, 
    {
        pop_value = stackPop(&cpu->stack, err) + stackPop(&cpu->stack, err);
        stackPush(&cpu->stack, &pop_value);
    }
)
DEF_CMD (SUB,   4,  0, 
    {
        first_pop = stackPop(&cpu->stack, err);
        second_pop = stackPop(&cpu->stack, err);
        sub_result = second_pop - first_pop;
        stackPush(&cpu->stack, &sub_result);
    }
)
DEF_CMD (MUL,   5,  0, 
    {
        pop_value = (stackPop(&cpu->stack, err)) * (stackPop(&cpu->stack, err));
        stackPush(&cpu->stack, &pop_value);
    }
)
DEF_CMD (DIV,   6,  0, 
    {
        if (cpu->stack.data[cpu->stack.size - 1] != 0)
            {
                first_pop = stackPop(&cpu->stack, err);
                second_pop = stackPop(&cpu->stack, err);
                div_result = (int)(second_pop / first_pop);
                stackPush(&cpu->stack, &div_result);
            }
            else
            {
                printf("attempt to divide by 0\n");
            }
    }
)
DEF_CMD (OUT,   7,  0, 
)
DEF_CMD (IN,   8,  0, 
)
DEF_CMD (HLT,   9,  0, 
    {
        return 0;
    }
)
DEF_CMD (CALL, 10,  0, 
)
DEF_CMD (SQRT, 11,  0, 
    {
        pop_value = stackPop(&cpu->stack, err);
        if (pop_value < 0)
        {
            printf("sqrt of number that < 0");
        }
        else 
        {
            sqrt_result = MySqrt(pop_value);
            stackPush(&cpu->stack, &sqrt_result);
        }
    }
)
DEF_CMD (CPY,  12,  0, 
    {
        pop_value = stackPop(&cpu->stack, err);
        stackPush(&cpu->stack, &pop_value);
        stackPush(&cpu->stack, &pop_value);
    }
)
DEF_JMP(JB, 13, <)

DEF_JMP(JBE, 14, <=)

DEF_JMP(JA, 15, >)

DEF_JMP(JAE, 16, >=)

DEF_JMP(JE, 17, ==)

DEF_JMP(JNE, 18, !=)


DEF_CMD (FACT, 20,  0, 
)
DEF_CMD(PRNT, 21, 0,
    {
        printf("0");
    }
)
DEF_CMD(ENDL, 22, 0,
    {
        printf("\n");
    }
)
DEF_CMD(SPACE, 22, 0,
    {
        printf(" ");
    }
)



#include "asm.h"

int main()
{
    int code[MAX_COMMANDS] ={};
    int labels[MAX_LABEL_SIZE] = {};
    ReadFile(code, labels);
    for (int i = 0; i < 15; i++)
    {
        printf("label %d\n", labels[i]);
    }
    ReadFile(code, labels);
    for (int i = 0; i < 10; i++)
    {
        printf("label %d\n", labels[i]);
    }
    return 0;
}

//================================================================

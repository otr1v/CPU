#include "asm.h"
#include "asmfunc.h"

int main(int argc, char* argv[])
{
    ASM asmus = {};
    CreateAsm(&asmus);
    if (argc > 1)
    {
        ReadFile(&asmus, argv[1]);
        for (int i = 0; i < 15; i++)
        {
            printf("label %d\n", asmus.labels[i]);
        }
        ReadFile(&asmus, argv[1]);
        for (int i = 0; i < 10; i++)
        {
            printf("label %d\n", asmus.labels[i]);
        }
    }
    else
    {
        printf("add file name in command line");
        return 0;
    }
    
    return 0;
}

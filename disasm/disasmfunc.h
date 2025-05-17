#include "disasm.h"
#include "filesize.h"

void ReadBinary()
{
    FILE* asmcode = fopen("out.bin", "rb");
    int size_buf = FileSize(asmcode);
    int* code = (int *) calloc((size_buf / sizeof(int)) + 1, sizeof(int));
    fread(code, sizeof(int), size_buf, asmcode);
    fclose(asmcode);

    FILE* out = fopen("output.txt", "w");

    fprintf(out, "ASM 2\n");
    
    size_t counter = 0;
    
    while (counter != (size_buf / sizeof(int)))
    {
        if ((code[counter] & CMD_MASK) == CMD_PUSH)
        {
            fprintf(out, "PUSH ");

            if (((code[counter] & ARG_IMMED) == ARG_IMMED) && ((code[counter] & ARG_RAM)!= ARG_RAM))
            {
                counter++;
                fprintf(out, "%d\n", code[counter++]);
            }
            else if ((code[counter] & ARG_RAM) == ARG_RAM)
            {
                counter++;
                fprintf(out, "[%d]\n", code[counter++]);
            }
            else if ((code[counter] &  ARG_REG) == ARG_REG)
            {
                counter++;
              
                #define CompRegs(register)                  \
                    if (code[counter] == REG_##register)     \
                        {                                     \
                            fprintf(out, #register"\n");       \
                            counter++;                          \
                        }                                        \
                    else
                
                #include "comparison_of_regs.h"
                /*else*/
                {
                    printf("syntax error");
                    counter++;
                }

            }
            
            else
            {
                printf("error");
                counter++;
            }
        }
        else if ((code[counter] & CMD_MASK) == CMD_POP)
        {
            fprintf(out, "pop ");
            if ((code[counter] &  ARG_REG) == ARG_REG)
            {
                counter++;

                #include "comparison_of_regs.h"
               
                /*else*/
                {
                    counter++;
                    printf("syntax error");
                }
            }
            else
            {
                counter++;
            }
        } 
        #define DEF_CMD(name, num, arg, ...)                 \
                else if ((code[counter] & CMD_MASK) == num)      \
                {                                              \
                    if (arg == 0)      \
                    {                                            \
                        fprintf(out, #name"\n");                  \
                        if ((code[counter] & CMD_MASK) >= CMD_JB && \
                            (code[counter] & CMD_MASK) <= CMD_JNE) \
                        {                                      \
                            fprintf(out, " %d\n", code[++counter]); \
                        }                                        \
                    }                                               \
                    counter++;                                        \
                }                                                    
        #define DEF_JMP(name, num, ...)       \
                DEF_CMD(name, num, 1, ...)                                                              

        #include "cmd.h"
        #undef DEF_CMD     
        else
        {
            counter++;
            printf("\n");
            printf("no such command has found");
            printf("%ld\n", counter);
        }
        #undef CompRegs
    }
    free(code);
    fclose(out);
}


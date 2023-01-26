#include "disasm.h"
#include "filesize.cpp"

void ReadBinary()
{
    FILE* asmcode = fopen("out.bin", "rb");
    int size_buf = FileSize(asmcode);
    int* code = (int *) calloc((size_buf / sizeof(int)) + 1, sizeof(int));
    fread(code, sizeof(int), size_buf, asmcode);
    fclose(asmcode);

    FILE* out = fopen("output.txt", "w");

    fprintf(out, "ASM 2\n");
    
    int counter = 0;
    
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
                
                #include "comparison_regs.h"
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
        #define DEF_CMD(name, num, arg, ...)                 \
                else if ((code[counter] & CMD_MASK) == num)      \
                {                                              \
                    if (arg == 0)      \
                    {                                            \
                        fprintf(out, #name"\n");                  \
                    }                                               \
                    counter++;                                        \
                }                                                    \
                                                                      \
                

        #include "cmd.h"
        #undef DEF_CMD
      
        // else if((code[counter] & CMD_MASK) == CMD_JE)
        // {
        //     fprintf(out, "je :");
        //     counter++;
        //     int label = code[counter++];
        //     fprintf(out, "%d\n", label);
        // }
        // else if((code[counter] & CMD_MASK) == CMD_JB)
        // {
        //     fprintf(out, "jb :");
        //     counter++;
        //     int label = code[counter++];
        //     fprintf(out, "%d\n", label);
        // }
      
        
        else if((code[counter] & CMD_MASK) == CMD_POP)
        {
            fprintf(out, "pop ");
            if ((code[counter] &  ARG_REG) == ARG_REG)
            {
                counter++;

                #include "comparison_regs.h"
               
                /*else*/
                {
                    counter++;
                    printf("syntax error");
                }
            }
            else
            {
                counter++;
                // printf("");
            }
        }
        else
        {
            counter++;
            printf("\n");
            printf("no such command has found");
            printf("%d\n", counter);
        }
        #undef CompRegs
    }
    free(code);
    fclose(out);
}


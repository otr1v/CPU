#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

void ReadBinary();
int FileSize(FILE* fp);

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)

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
    CMD_JE  = 14,
    NO_MEMORY,
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

const int CMD_MASK            = 0xF;
const int ARG_IMMED           = 1 << 5;
const int ARG_REG             = 1 << 6;
const int ARG_RAM             = 1 << 7;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int REG_REX             = 4;
const int REG_RFX             = 5;


int main()
{
    ReadBinary();

    return 0;
}

void ReadBinary()
{
    FILE* asmcode = fopen("out.bin", "rb");
    int size_buf = FileSize(asmcode);
    int* code = (int *) calloc((size_buf / sizeof(int)) + 1, sizeof(int));
    fread(code, sizeof(int), size_buf, asmcode);
    fclose(asmcode);
    printf("dead");
    FILE* out = fopen("output.txt", "w");

    fprintf(out, "ASM 2\n");
    
    int counter = 0;
    
    while (counter != (size_buf / sizeof(int)))
    {
        if ((code[counter] & CMD_MASK) == CMD_PUSH)
        {
            fprintf(out, "push ");

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

                if (code[counter] == REG_RAX)
                {
                    fprintf(out, "rax\n");
                    counter++;
                    
                }
                else if (code[counter] == REG_RBX)
                {
                    fprintf(out, "rbx\n");
                    counter++;
                }
                else if (code[counter] == REG_RCX)
                {
                    fprintf(out, "rcx\n");
                    counter++;
                }
                else if (code[counter] == REG_RDX)
                {
                    fprintf(out, "rdx\n");
                    counter++;
                }
                else if (code[counter] == REG_REX)
                {
                    fprintf(out, "rex\n");
                    counter++;
                }
                else if (code[counter] == REG_RFX)
                {
                    fprintf(out, "rfx\n");
                    counter++;
                }
                else
                {
                    counter++;
                    printf("схуяли");
                }
            }
            
            else
            {
                printf("error");
                counter++;
            }
        }
        else if ((code[counter] & CMD_MASK) == CMD_ADD)
        {
            fprintf(out, "add\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_HLT)
        {
            fprintf(out, "hlt\n");
            counter++;
        }
        else if((code[counter] & CMD_MASK) == CMD_JE)
        {
            fprintf(out, "je :");
            counter++;
            int label = code[counter++];
            fprintf(out, "%d\n", label);
        }
        else if((code[counter] & CMD_MASK) == CMD_JB)
        {
            fprintf(out, "jb :");
            counter++;
            int label = code[counter++];
            fprintf(out, "%d\n", label);
        }
        else if ((code[counter] & CMD_MASK) == CMD_SQRT)
        {
            fprintf(out, "sqrt\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_CPY)
        {
            fprintf(out, "cpy\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_MUL)
        {
            fprintf(out, "mul\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_DIV)
        {
            fprintf(out, "div\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_SUB)
        {
            fprintf(out, "sub\n");
            counter++;
        }
        else if ((code[counter] & CMD_MASK) == CMD_POP)
        {
            fprintf(out, "pop ");
            if ((code[counter] &  ARG_REG) == ARG_REG)
            {
                counter++;

                if (code[counter] == REG_RAX)
                {
                    fprintf(out, "rax\n");
                    counter++;
                    
                }
                else if (code[counter] == REG_RBX)
                {
                    fprintf(out, "rbx\n");
                    counter++;
                }
                else if (code[counter] == REG_RCX)
                {
                    fprintf(out, "rcx\n");
                    counter++;
                }
                else if (code[counter] == REG_RDX)
                {
                    fprintf(out, "rdx\n");
                    counter++;
                }
                else if (code[counter] == REG_REX)
                {
                    fprintf(out, "rex\n");
                    counter++;
                }
                else if (code[counter] == REG_RFX)
                {
                    fprintf(out, "rfx\n");
                    counter++;
                }
                else
                {
                    counter++;
                    printf("схуяли");
                }
            }
            else
            {
                counter++;
                printf("блять");
            }
        }
        else
        {
            counter++;
            printf("\n");
            printf("%d\n", counter);
        }
    }
    fclose(out);
}

//================================================

int FileSize(FILE* fp)
{
    struct stat buffer = {};
    int res_fstat = fstat(fileno(fp), &buffer);
    CHECK_ERR(res_fstat == -1, "can't fill the structure stat", ERR_FSTAT);
    int size_buf = buffer.st_size;
    return size_buf;
}

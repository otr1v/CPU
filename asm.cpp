#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)
// #define DEF_CMD(name, num, arg) \
//         CMD_##name = num,
// enum 
// {
//     #include "cmd.h"
// }
// #undef DEF_CMD

// #define DEF_CMD(name, num, arg) \
//             if (strcmp(cmd, #name) == 0) \
//                 {code[ip++] = num;   \
//                 if (arg) GetArgs();}   \
//                 else

;

const int MAX_LABEL_SIZE      = 6;
const int MAX_COMMANDS        = 100;
const int AMOUNT_OF_REGISTERS = 20;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int MASK_IMMED          = 1 << 5;
const int MASK_REGISTER       = 1 << 6;
const int MASK_RAM            = 1 << 7;

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
    NO_MEMORY,
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

int* ReadFile(int code[], int labels[]);
int FileSize(FILE* fp);
int CounterStrings(FILE* fp, int size_buf, char* buf);
int* ReadCommands(int code[], int num_of_commands, char** text, int labels[]);
void ClearArray(int code[]);

int main()
{
    int code[MAX_COMMANDS] ={};
    int labels[MAX_LABEL_SIZE] = {};
    int registers[AMOUNT_OF_REGISTERS] = {};
    // FILE* fp = fopen("out.bin", "wb");
    // fwrite(code, sizeof(int), 100, fp);
    ReadFile(code, labels);
    ReadFile(code, labels);
    for (int i = 0; i < 20; i++)
    {
        printf("%d\n", code[i]);
    }
    return 0;
}

//================================================================

int* ReadFile(int code[], int labels[])
{
    FILE* fp = fopen("input.txt", "r");
    int size_buf = FileSize(fp);
    char* buf = (char *) calloc(size_buf + 1, sizeof(char));
    fread(buf, sizeof(char), size_buf, fp);

    int n_strings = CounterStrings(fp, size_buf, buf);
    
    char** text = (char **) calloc(n_strings + 1, sizeof(char*));

    int counter_text = 0;
    for (int j = 0; j < size_buf; j++)
    {
        if (j == 0)
        {
            text[0] = &buf[0];
            counter_text++;
        }
        if (buf[j] == '\n')
        {
            text[counter_text] = &buf[j + 1];
            counter_text++;
        }
    }

    char sign[5] = "";
    int version  = 0, symb_read = 0, read = 0;

    sscanf(text[0], "%s%n", sign, &symb_read);
    sscanf(text[0] + symb_read, "%d%n", &version, &read);

    if (strcmp(sign, "ASM") != 0 || version != 2)
    {
        exit(EXIT_FAILURE);
    }
    int num_of_commands = n_strings;
    ClearArray(code);

    ReadCommands(code, num_of_commands, text, labels);
    
    return code;
}

//=======================================================

int FileSize(FILE* fp)
{
    struct stat buffer = {};
    int res_fstat = fstat(fileno(fp), &buffer);
    CHECK_ERR(res_fstat == -1, "can't fill the structure stat", ERR_FSTAT);
    int size_buf = buffer.st_size;
    return size_buf;
}

//==============================================================

int CounterStrings(FILE* fp, int size_buf, char* buf)
{
    int n_strings = 0;
    for (int i = 0; i < size_buf; i++)
    {
        if (buf[i] == '\n' || buf[i] == EOF)
        {
            n_strings += 1;
        }
    }
    return n_strings;
}

//=======================================================================

int* ReadCommands(int code[], int num_of_commands, char** text, int labels[])
{
    FILE* out = fopen("out.bin", "wb");

    int current_line = 1;
    int ip = 0;
    while (current_line != (num_of_commands))
    {
        char cmd[5] = "";
        int read_symbols = 0;
        sscanf(text[current_line], "%s%n", cmd, &read_symbols);
        if (strcmp("push", cmd) == 0)
        {
            int val = 0;
            sscanf(text[current_line] + read_symbols, "%d", &val);
            code[ip++]   = CMD_PUSH;
            code[ip++] = val;
        }
        if (strcmp("add", cmd) == 0)
        {
            code[ip++] = CMD_ADD;
        }
        int label = 0;
        char ch;
        if (sscanf(text[current_line], "%d%c", &label, &ch) == 2)
        {
            labels[label] = current_line;
            // printf("what\n");
            // printf("label %d\n", labels[label]);
        }
        if (strcmp("jump", cmd) == 0)
        {
            //printf("read symb%d\n", read_symbols);
            code[ip++] = CMD_JMP;
            if (sscanf(text[current_line] + read_symbols + 1, "%c%d", &ch, &label) == 2)
            {
                //printf("read label %d", label);
                if (labels[label] != 0)
                {
                    current_line = labels[label];
                   // printf("current line %d\n", current_line);

                }
                //printf("question");
            };
        }
        if (strcmp("div", cmd) == 0)
        {
            code[ip++] = CMD_DIV;
        }
        if (strcmp("hlt", cmd) == 0)
        {
            code[ip++] = CMD_HLT;
            printf("%d\n", ip);
        }
        if (ip > 100)
        {
            return code;
        }
        current_line++;
    }
    fwrite(code, sizeof(int), num_of_commands, out);
    fclose(out);
    return code;
}

//===========================================================================

void ClearArray(int code[])
{
    for (int i = 0; i < MAX_COMMANDS; i++)
    {
        code[i] = 0;
    }
}

//==================================================================================

int getargs(int code[], char** text, char cmd[], int read_symbols, int current_line, int* ip, int registers[])
{
    int command = 0;
    int val = 0;
    char reg[6] = {};
    if (strcmp("push", cmd) == 0)
    {
        command = CMD_PUSH;
        if (sscanf(text[current_line] + read_symbols, "%d", &val) == 1)
        {
            command |= MASK_IMMED;
        }
        if (sscanf(text[current_line] + read_symbols, "%s", &reg) == 1)
        {
            command |= MASK_REGISTER;
            if (strcmp(reg, "rax") == 0)
            {
                val = registers[REG_RAX];
            }
            else if (strcmp(reg, "rbx") == 0)
            {
                val = registers[REG_RBX];
            }
            else if (strcmp(reg, "rcx") == 0)
            {
                val = registers[REG_RCX];
            }
            else if (strcmp(reg, "rdx") == 0)
            {
                val = registers[REG_RDX];
            }
            else
            {
                printf("syntax error\n");
            }
            
        }
        // if (sscanf(text[current_line] + read_symbols, "%d", &val) == 1)
        // {
        //     command |= MASK_RAM;
        // }
        code[*ip++] = command;
        code[*ip++] = val;
    }
    if (strcmp(cmd, "pop") == 0)
    {
        command = CMD_POP;
        if (sscanf(text[current_line] + read_symbols, "%d", &val) == 1)
        {
            command |= MASK_IMMED;
        }
        if (sscanf(text[current_line] + read_symbols, "%s", &reg) == 1)
        {
            command |= MASK_REGISTER;
        }
    }
}

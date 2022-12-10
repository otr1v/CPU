#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

const int MAX_LABEL_SIZE      = 300;
const int MAX_COMMANDS        = 100;
const int AMOUNT_OF_REGISTERS = 20;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int MASK_IMMED          = 1 << 5;
const int MASK_REGISTER       = 1 << 6;
const int MASK_RAM            = 1 << 7;
const int AMOUNT_OF_RAM       = 15;

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
    CMD_JA   = 14,
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
int ReadArgs(int code[], char** text, char cmd[], int read_symbols, int current_line, int* ip);


int main()
{
    int code[MAX_COMMANDS] ={};
    int labels[MAX_LABEL_SIZE] = {};
    // int registers[AMOUNT_OF_REGISTERS] = {1, 2};
    // int ram[AMOUNT_OF_RAM] = {5, 4, 3, 2, 1};
    // FILE* fp = fopen("out.bin", "wb");
    // fwrite(code, sizeof(int), 100, fp);
    
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

int* ReadFile(int code[], int labels[])
{
    FILE* input = fopen("factorial.txt", "r");
    int size_buf = FileSize(input);
    char* buf = (char *) calloc(size_buf + 1, sizeof(char));
    fread(buf, sizeof(char), size_buf, input);
    fclose(input);
    int n_strings = CounterStrings(input, size_buf, buf);
    
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
   // printf("num%d", num_of_commands);
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
    printf("num : %d", num_of_commands);
    while (current_line != (num_of_commands + 1))
    {
        char cmd[5] = "";
        int read_symbols = 0;
        sscanf(text[current_line], "%s%n", cmd, &read_symbols);
        if (strcmp("push", cmd) == 0)
        {
            int val = ReadArgs(code, text, cmd, read_symbols, current_line, &ip);
            printf("value = %d\n", val);
            // sscanf(text[current_line] + read_symbols, "%d", &val);
            // code[ip++]   = CMD_PUSH;
            // code[ip++] = val;
        }
        else if (strcmp("add", cmd) == 0)
        {
            code[ip++] = CMD_ADD;
        }
        int label = 0;
        char ch;
        if (sscanf(text[current_line], "%d%c", &label, &ch) == 2)
        {
            printf("labeeel%d%c\n\n", label, ch);
            if (ch == ':')
            {
                labels[label] = ip;
            }
            // printf("what\n");
            printf("label %d\n", labels[label]);
        }
        if (strcmp("jmp", cmd) == 0)
        {
            //printf("read symb%d\n", read_symbols);
            code[ip++] = CMD_JMP;
            
            int spaces = 0;
            while (sscanf(text[current_line] + read_symbols + spaces, "%c", &ch) == 1 && (isspace(ch) > 0))
            {
                spaces++;
            }
            if (sscanf(text[current_line] + read_symbols + spaces, "%c%d", &ch, &label) == 2) 
            {
                //printf("read label %d", label);
                if (labels[label] != 0)
                {
                    code[ip++] = labels[label] + 1;
                   // printf("current line %d\n", current_line);

                }
                //printf("question");
            };
        }
        if (strcmp(cmd, "ja") == 0)
        {
            code[ip++] = CMD_JA;
            int spaces = 0;
            while (sscanf(text[current_line] + read_symbols + spaces, "%c", &ch) == 1 && (isspace(ch) > 0))
            {
                spaces++;
            }
            if (sscanf(text[current_line] + read_symbols + spaces, "%c%d", &ch, &label) == 2) 
            {
                if (labels[label] != 0)
                {
                    code[ip++] = labels[label] + 1;
                }
            };

        }
        else if (strcmp("div", cmd) == 0)
        {
            code[ip++] = CMD_DIV;
        }
        else if (strcmp("hlt", cmd) == 0)
        {
            code[ip++] = CMD_HLT;
            printf("nooooooo%d\n", ip);
        }
        else if (strcmp("pop", cmd) == 0)
        {
            ReadArgs(code, text, cmd, read_symbols, current_line, &ip);
        }
        else if (strcmp(cmd, "mul") == 0)
        {
            code[ip++] = CMD_MUL;
        }
        else if (strcmp(cmd, "sqrt") == 0)
        {
            code[ip++] == CMD_SQRT;
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            code[ip++] = CMD_SUB;
        }
        else if (strcmp(cmd, "pow2") == 0)
        {
            code[ip++] = CMD_POW2;
        }
        else if (strcmp(cmd, "cpy") == 0)
        {
            code[ip++] = CMD_CPY;
        }
       
        if (ip > 100)
        {
            return code;
        }
        current_line++;
    }
    for (int i = 0; i < 30; i++)
    {
        printf("%d code :%d\n", i, code[i]);
    }
    printf("ipiaad%d", ip);
    fwrite(code, sizeof(int), ip, out);
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

int ReadArgs(int code[], char** text, char cmd[], int read_symbols, int current_line, int* ip)
{
    int command = 0;
    int val = 0;
    char reg[6] = {};

    int counter = 0; // check if command is ram/reg or immed

    if (strcmp("push", cmd) == 0)
    {
        char ch1 = ' ', ch2 =' ';

        command = CMD_PUSH;
        printf("return value is %d\n", sscanf(text[current_line] + read_symbols, "%c %d %c", &ch1, &val, &ch2));
        printf("%c %c\n", ch1, ch2);
        if (sscanf(text[current_line] + read_symbols, "%d", &val) == 1)
        {
            // printf("value %d", val);
            command |= MASK_IMMED;
            counter++;
        }
        else if ((sscanf(text[current_line] + read_symbols, "%c", &ch1) == 1))
        {
            char* ptr = text[current_line] + read_symbols + 1;
            while (ch1 == ' ')
            {
                sscanf(ptr, "%c", &ch1);
                ptr++;
            }
            if ((ch1 == '[') && (sscanf(ptr, "%d %c", &val, &ch1) == 2))
            {
                command |= MASK_RAM;
                command |= MASK_IMMED;
                counter++;
            }
        }
        if ((sscanf(text[current_line] + read_symbols, "%s", reg) == 1) && (counter == 0))
        {
            command |= MASK_REGISTER;
            // printf("%s\n", reg);
            if (strcmp(reg, "rax") == 0)
            {
                val = REG_RAX;
            }
            else if (strcmp(reg, "rbx") == 0)
            {
                val = REG_RBX;
            }
            else if (strcmp(reg, "rcx") == 0)
            {
                val = REG_RCX;
            }
            else if (strcmp(reg, "rdx") == 0)
            {
                val = REG_RDX;
            }
            else
            {
                printf("lolsyntax error\n");
            }

            counter++;
        }
        
        if (counter == 0)
        {
            printf("syntax error : there wasn't these type of command\n\n");
        }
        printf("command :%d\n", command);
        code[(*(ip))++] = command;
        printf("ip :%d\n", *ip);
        code[(*(ip))++] = val;
    }
    else if (strcmp(cmd, "pop") == 0)
    {
        command = CMD_POP;
        command |= MASK_REGISTER;
        code[(*(ip))++] = command;
        if (sscanf(text[current_line] + read_symbols, "%s", reg) == 1)
        {
            if (strcmp(reg, "rax") == 0)
            {
                val = REG_RAX;
            }
            else if (strcmp(reg, "rbx") == 0)
            {
                val = REG_RBX;
            }
            else if (strcmp(reg, "rcx") == 0)
            {
                val = REG_RCX;
            }
            else if (strcmp(reg, "rdx") == 0)
            {
                val = REG_RDX;
            }
            else
            {
                printf("lolsyntax error\n");
            }
        }
        else
        {
            printf("syntax error");
        }
        code[(*(ip))++] = val;

    }
    return val;
}

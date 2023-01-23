#include "asm.h"
#include "filesize.cpp"
void CreateAsm(ASM* asmstruct)
{
    asmstruct->read_symbols = 0;
    asmstruct->current_line = 0;
    for (int i = 0; i < MAX_LABEL_SIZE; i++)
    {
        asmstruct->labels[i] = 0;
    }
    for (int j = 0; j < MAX_COMMANDS; j++)
    {
        asmstruct->code[j] = 0;
    }
    asmstruct->text = NULL;
}

int* ReadFile(ASM* asmstruct, char* filename)
{
    FILE* input = fopen(filename, "r");
    int size_buf = FileSize(input);
    char* buf = (char *) calloc(size_buf + 1, sizeof(char));
    fread(buf, sizeof(char), size_buf, input);
    fclose(input);
    int n_strings = CounterStrings(size_buf, buf);
    
    asmstruct->text = (char **) calloc(n_strings + 1, sizeof(char*));

    int counter_text = 0;
    for (int j = 0; j < size_buf; j++)
    {
        if (j == 0)
        {
            asmstruct->text[0] = &buf[0];
            counter_text++;
        }
        if (buf[j] == '\n')
        {
            asmstruct->text[counter_text] = &buf[j + 1];
            counter_text++;
        }
    }

    char sign[5] = "";
    int version  = 0, symb_read = 0, read = 0;

    sscanf(asmstruct->text[0], "%s%n", sign, &symb_read);
    sscanf(asmstruct->text[0] + symb_read, "%d%n", &version, &read);

    if (strcmp(sign, "ASM") != 0 || version != 2)
    {
        printf("wrong file version");
        return NULL;
    }
    int num_of_commands = n_strings;
   // printf("num%d", num_of_commands);
    ClearArray(asmstruct->code);

    WriteCommands(asmstruct, num_of_commands);
    
    return asmstruct->code;
}

//==============================================================

int CounterStrings(int size_buf, char* buf)
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

int* WriteCommands(ASM* asmstruct, int num_of_commands)
{
    FILE* out = fopen("out.bin", "wb");

    asmstruct->current_line = 1;
    int ip = 0;
    printf("num : %d", num_of_commands);
    while (asmstruct->current_line != (num_of_commands + 1))
    {
        char cmd[MAX_SIZE_OF_COMMAND] = "";
        asmstruct->read_symbols = 0;
        sscanf(asmstruct->text[asmstruct->current_line], "%s%n", cmd, &(asmstruct->read_symbols));
        if (strcmp("push", cmd) == 0)
        {
            int val = ReadArgs(asmstruct, cmd, &ip);
            printf("value = %d\n", val);
            // sscanf(text[current_line] + read_symbols, "%d", &val);
            // code[ip++]   = CMD_PUSH;
            // code[ip++] = val;
        }
        else if (strcmp("add", cmd) == 0)
        {
            asmstruct->code[ip++] = CMD_ADD;
        }
        int label = 0;
        char ch;
        if (sscanf(asmstruct->text[asmstruct->current_line], "%d%c", &label, &ch) == 2)
        {
            printf("labeeel%d%c\n\n", label, ch);
            if (ch == ':')
            {
                asmstruct->labels[label] = ip;
            }
            // printf("what\n");
            printf("label %d\n", asmstruct->labels[label]);
        }
        if (strcmp("jmp", cmd) == 0)
        {
            //printf("read symb%d\n", read_symbols);
            asmstruct->code[ip++] = CMD_JMP;
            
            int spaces = 0;
            while (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols + spaces, "%c", &ch) == 1 && (isspace(ch) > 0))
            {
                spaces++;
            }
            if (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols + spaces, "%c%d", &ch, &label) == 2) 
            {
                //printf("read label %d", label);
                if (asmstruct->labels[label] != 0)
                {
                    asmstruct->code[ip++] = asmstruct->labels[label] + 1;
                   // printf("current line %d\n", current_line);

                }
                //printf("question");
            };
        }
        if ((strcmp(cmd, "jb") == 0) || (strcmp(cmd, "je") == 0))
        {
            if ((strcmp(cmd, "jb") == 0))
            {
                asmstruct->code[ip++] = CMD_JB;
            }
            else
            {
                asmstruct->code[ip++] = CMD_JE;
            }
            int spaces = 0;
            while (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols + spaces, "%c", &ch) == 1 && (isspace(ch) > 0))
            {
                spaces++;
            }
            if (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols + spaces, "%c%d", &ch, &label) == 2) 
            {
                if (asmstruct->labels[label] != 0)
                {
                    asmstruct->code[ip++] = asmstruct->labels[label] + 1;
                }
            };

        }
        if (strcmp(cmd, "factorial") == 0)
        {

        }
        
        else if (strcmp("div", cmd) == 0)
        {
            asmstruct->code[ip++] = CMD_DIV;
        }
        else if (strcmp("hlt", cmd) == 0)
        {
            asmstruct->code[ip++] = CMD_HLT;
            printf("nooooooo%d\n", ip);
        }
        else if (strcmp("pop", cmd) == 0)
        {
            ReadArgs(asmstruct, cmd, &ip);
        }
        else if (strcmp(cmd, "mul") == 0)
        {
            asmstruct->code[ip++] = CMD_MUL;
        }
        else if (strcmp(cmd, "sqrt") == 0)
        {
            asmstruct->code[ip++] = CMD_SQRT;
        }
        else if (strcmp(cmd, "sub") == 0)
        {
            asmstruct->code[ip++] = CMD_SUB;
        }
        else if (strcmp(cmd, "cpy") == 0)
        {
            asmstruct->code[ip++] = CMD_CPY;
        }
        else if (strcmp(cmd, "call") == 0)
        {
            asmstruct->code[ip++] = CMD_CALL;
        }
        if (ip > 100)
        {
            return asmstruct->code;
        }
        asmstruct->current_line++;
    }
    for (int i = 0; i < 55; i++)
    {
        printf("%d code :%d\n", i, asmstruct->code[i]);
    }
    printf("ipiaad%d", ip);
    fwrite(asmstruct->code, sizeof(int), ip, out);
    fclose(out);
    return asmstruct->code;
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

int ReadArgs(ASM* asmstruct, char cmd[], int* ip)
{
    int command = 0;
    int val = 0;
    char reg[6] = {};

    int counter = 0; // check if command is ram/reg or immed

    if (strcmp("push", cmd) == 0)
    {
        char ch1 = ' ', ch2 =' ';

        command = CMD_PUSH;
        printf("return value is %d\n", sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols, "%c %d %c", &ch1, &val, &ch2));
        printf("%c %c\n", ch1, ch2);
        if (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols, "%d", &val) == 1)
        {
            // printf("value %d", val);
            command |= MASK_IMMED;
            counter++;
        }
        else if ((sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols, "%c", &ch1) == 1))
        {
            char* ptr = asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols + 1;
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
        if ((sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols, "%s", reg) == 1) && (counter == 0))
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
            else if (strcmp(reg, "rex") == 0)
            {
                val = REG_REX;
            }
            else if (strcmp(reg, "rfx") == 0)
            {
                val = REG_RFX;
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
        asmstruct->code[(*(ip))++] = command;
        printf("ip :%d\n", *ip);
        asmstruct->code[(*(ip))++] = val;
    }
    else if (strcmp(cmd, "pop") == 0)
    {
        command = CMD_POP;
        command |= MASK_REGISTER;
        asmstruct->code[(*(ip))++] = command;
        if (sscanf(asmstruct->text[asmstruct->current_line] + asmstruct->read_symbols, "%s", reg) == 1)
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
            else if (strcmp(reg, "rex") == 0)
            {
                val = REG_REX;
            }
            else if (strcmp(reg, "rfx") == 0)
            {
                val = REG_RFX;
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
        asmstruct->code[(*(ip))++] = val;

    }
    return val;
}

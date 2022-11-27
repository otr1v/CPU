#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../stack/func.cpp"

void ReadAsm(FILE * asmcode, stack_type* stk);
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

    
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};

int main()
{

    FILE * asmcode = NULL;
    
    stack_type stack = {};
    stackCreator_(&stack, 5);
    ReadAsm(asmcode, &stack);
    return 0;
}

//==============================================================================

void ReadAsm(FILE * asmcode, stack_type* stk)
{
    int* err = {};
    elem_t pop_value1 = POISON;
    elem_t pop_value2 = POISON;
    elem_t pop_value  = POISON;
    asmcode = fopen("out.bin", "rb");
    int size_buf = FileSize(asmcode);
    int code [size_buf / sizeof(int)];
    
    fread(code, sizeof(int), size_buf, asmcode);
    for (int i = 0; i < size_buf / sizeof(int); i++)
    {
        printf("%d\n", code[i]);
    }
    
    int ip = 0;
   // printf("%ld\n", size_buf / sizeof(int));
    while(ip !=  ((size_buf / sizeof(int)) ))
    {
        // printf("%d\n", ip);
        // printf("In stack %d\n", stk->data[stk->size - 1]);

        switch (code[ip])
        {
        case CMD_PUSH:
            stackPush(stk, &code[ip + 1]);
            // printf("code : %d\n", stk->data[stk->size - 1]);
            ip += 2;
            break;
        case CMD_ADD:
            // printf("In stack %d\n", stk->data[stk->size]);
            stackPop(stk, err, &pop_value1);
            // printf("In stack %d\n", stk->data[stk->size]);
            stackPop(stk, err, &pop_value2);
            // printf("pop value1 = %d\n", pop_value1);
            // printf("pop value2 = %d\n", pop_value2);
            pop_value = pop_value1 + pop_value2;
            //printf("pop value = %d\n", pop_value);
            stackPush(stk, &pop_value);
            ip += 1;
            break;
        default:
            break;
        }
    }
    //printf("%d\n", stk -> data[0]);
}

//=================================================================================

int FileSize(FILE* fp)
{
    struct stat buffer = {};
    int res_fstat = fstat(fileno(fp), &buffer);
    CHECK_ERR(res_fstat == -1, "can't fill the structure stat", ERR_FSTAT);
    int size_buf = buffer.st_size;
    return size_buf;
}

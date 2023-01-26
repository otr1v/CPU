#define DEF_CMD(name, num, arg, ...)    \
    CMD_##name = num,

enum 
{
    #include "cmd.h"
    NO_MEMORY,
    ERR_OPEN_FILE, 
    BAD_FREAD
};

#undef DEF_CMD

const int ARG_IMMED           = 1 << 6;
const int ARG_REG             = 1 << 7;
const int ARG_RAM             = 1 << 8;
const int AMOUNT_OF_REGISTERS = 20;
const int NUMBER_OF_RAM_ELEMS = 100;
const int CMD_MASK            = 0x1F;
const int REG_RAX             = 0;
const int REG_RBX             = 1;
const int REG_RCX             = 2;
const int REG_RDX             = 3;
const int REG_REX             = 4;
const int REG_RFX             = 5;

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)

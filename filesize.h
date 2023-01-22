#pragma once
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
        
enum 
{
    ERR_FSTAT = 20
};
int FileSize(FILE* fp);

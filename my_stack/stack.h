///\file
///\brief This header is all functions/const/defines
#ifndef STACK_HEADER
#define STACK_HEADER

#define MyAssert(condition, message)    \
        if (!(condition))                \
            printf("Error in %s in %d message: %s \n",       \
                    #condition, __LINE__, message);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
//! typedef element of stack data
typedef int elem_t;

//! typedef CANARY type
typedef unsigned long long CANARY_TYPE;

#define VAR_INFO
#define HASH

enum errCodes {
    STACK_OK                  = 0,
    STACK_NULL                = 1,
    STACK_DATA_NULL           = 1 << 1,
    BAD_POINTER               = 1 << 2,
    STACK_DELETED             = 1 << 3,
    DAMAGED_RIGHT_CANARY      = 1 << 4,
    DAMAGED_LEFT_CANARY       = 1 << 5,
    DAMAGED_LEFT_DATA_CANARY  = 1 << 6,
    DAMAGED_RIGHT_DATA_CANARY = 1 << 7
};

//! typedef struct stack
typedef struct stack_type 
{
    CANARY_TYPE LEFT_MASTER;
    elem_t* data;
    size_t size;
    size_t capacity;
    int error; // TODO errCodes 
    #ifdef DEBUG_INFO
        const char* func; 
        const char* file; 
        const char* name;
        int         line;
    #endif
    const char* name;
    CANARY_TYPE RIGHT_MASTER;
    #ifdef HASH
        unsigned int hash;
    #endif
} stack_type;
#define STACK_NAME(var)   \
    (#var);
// #ifdef DEBUG_INFO //TODO make it work
#define stackCreator(stack, number_of_elems)        \
    stackCreator_(&stack, number_of_elems, #stack, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    
// #endif

/// @brief This function creates stack
/// @param stack Structure stack 
/// @param number_of_elems Stack capacity
/// @return Structure stack
stack_type* stackCreator_(stack_type* stack, int number_of_elems);
/// @brief This function pushes an element to stack
/// @param stack Structure stack
/// @param value pushed value
/// @return code of error
int stackPush(stack_type* stack, elem_t* value);
/// @brief this function resizes stack
/// @param stack structure stack
/// @return error code of no memory
const int* stackResize(stack_type* stack);
/// @brief this function pops element from stack
/// @param stack structure stack
/// @param err error code of zero_elem_pop
/// @param pop_value value that will be popped
/// @return popped value
int stackPop(stack_type* stack, int *err);
/// @brief this function destroyes stack
/// @param stack structure stack
/// @return code of error
int stackDestroyer(stack_type* stack);
/// @brief this function counts all stack errors
/// @param stack structure stack
/// @return code of error
int stackError(stack_type* stack);
/// @brief this function writes all info about stack in a file
/// @param stack structure stack
/// @param err error code of zero_elem_pop 
/// @param name 
/// @param line 
/// @param function 
/// @param file 
/// @return 
int stackDump(stack_type* stack, int* err,  const char* name, const int line, const char* function, const char* file);
int Hash(const char* str, int len, stack_type* stack);

static const CANARY_TYPE LEFT_CANARY       = 0xBEADFACE; // TODO remove global const or add static
static const CANARY_TYPE RIGHT_CANARY      = 0xBAADF00D; // TODO remove global const or add static
static const CANARY_TYPE LEFT_DATA_CANARY  = 0xCAFEBABE; // TODO remove global const or add static
static const CANARY_TYPE RIGHT_DATA_CANARY = 0xDEADBABE; // TODO remove global const or add static
static const elem_t POISON = -2281337;                     // TODO remove global const or add static
static const int ZERO_ELEM_POP = -1;                   // TODO remove global const or add static
static const int* NO_MEMORY_FOR_RESIZE = (int*)0x666; // TODO remove global const or add static
static const int k_realloc = 2;                    // TODO remove global const or add stati
static const int size_destroyed_stk = INT_MAX; // TODO remove global const or add static
static const int capacity_destroyed_stk = -228; // TODO remove global const or add static

#endif

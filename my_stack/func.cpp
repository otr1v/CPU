///\file 
///\brief This file is functions
#ifndef ST
#define ST
#include "stack.h"

stack_type* stackCreator_(stack_type* stack, int number_of_elems)
{
    if (stack->data == NULL)
    {
        stack->data = (elem_t *) calloc(sizeof(CANARY_TYPE) * 2 + number_of_elems * sizeof(elem_t) + 0, sizeof(char));

        if (stack->data == NULL)
        {
            printf("can't give memory to create stack_data_array\n");
        }
      
        *(CANARY_TYPE *)(stack->data)                         = LEFT_DATA_CANARY;
        stack->data = stack->data + sizeof(CANARY_TYPE) / sizeof(elem_t);
        *(CANARY_TYPE *)(stack->data + number_of_elems)       = RIGHT_DATA_CANARY;
        stack->capacity = number_of_elems;
        for (size_t i = 0; i < (stack->capacity); i++)
        { 
            stack->data[i] = POISON;
        }
        stack->RIGHT_MASTER = RIGHT_CANARY;
        stack->LEFT_MASTER  = LEFT_CANARY;

        stack->size = 0;
        
        #ifdef DEBUG_INFO
            stack->line = __LINE__;
            stack->func = __PRETTY_FUNCTION__;
            stack->file = __FILE__;
            stack->name = name;
        #endif
    }
    stack->error = stackError(stack);
    if (stack->error != STACK_OK)
    {
        stackDump(stack, NULL, (stack->name), __LINE__, __PRETTY_FUNCTION__, __FILE__);
    }
    return stack;
}

//============================================================================================

int stackPush(stack_type* stack, elem_t* value)
{   // TODO add asserts here and everywhere
    MyAssert (value != NULL, "NULL_VALUE_PASSED");
  
    if (stack->size >= stack->capacity)
    {
        stackResize(stack);
    }
    stack->data[stack->size] = *(value);
    stack->size++;
    stack->error = stackError(stack);
    if (stack->error != STACK_OK)
    {
        stackDump(stack, NULL, (stack->name), __LINE__, __PRETTY_FUNCTION__, __FILE__);
    }
    return stack->error;
}

//=================================================================

const int* stackResize(stack_type* stack)
{
    stack->capacity *= k_realloc;                        
    stack->data = stack->data - (sizeof(CANARY_TYPE) / sizeof(elem_t));
    stack->data = (elem_t*) realloc((stack->data), ((stack->capacity) * sizeof(elem_t) + 2 * sizeof(CANARY_TYPE) + 0));
    if (stack->data == NULL)
    {
        printf("can't give memory to resize stack data array\n");
        return NO_MEMORY_FOR_RESIZE;
    }
    stack->data = stack->data + sizeof(CANARY_TYPE) / sizeof(elem_t);
    *(CANARY_TYPE *)(stack->data + stack->capacity) = RIGHT_DATA_CANARY;

    for (size_t i = (stack->size); i < (stack->capacity); i++)
    {
        memcpy(stack->data + i, &POISON, sizeof(elem_t));
    }

    stack->error = stackError(stack);
    if (stack->error != STACK_OK) 
    {
        stackDump(stack, NULL, (stack->name), __LINE__, __PRETTY_FUNCTION__, __FILE__);
    }
    return NULL;
}

//======================================================================

int stackPop(stack_type* stack, int *err) // 
{
    if ((stack->size) < 1)
    {
        printf("pop when size is 0, try another time\n");
        *err = ZERO_ELEM_POP; 
    }
    int tmp = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = POISON;
    stack->size--;
    stack->error = stackError(stack);
    if (stack->error != 0)
    {
        stackDump(stack, err, (stack->name), __LINE__, __PRETTY_FUNCTION__, __FILE__);
    }
    return tmp;
}

//=========================================================================

int stackDestroyer(stack_type* stack)
{
    memset(stack->data, POISON, stack->capacity);
    stack->size = size_destroyed_stk;
    stack->capacity = capacity_destroyed_stk;
    stack->error = stackError(stack);
    free(stack->data);
    return stack->error;
}

//=================================================================================

uint32_t hash(stack_type* stack)
{
    uint32_t hash = 5381;
    size_t i = 0;
    for (elem_t value = stack->data[i]; i != stack->capacity; i++)
    {
        hash = hash * 33 + value;
    }
    return hash;
}
//====================================================================================

int stackError(stack_type* stack)
{
    int sum_of_errors = 0;
    if (stack == NULL)
    {
        sum_of_errors |= STACK_NULL;
    }
    if ((stack->data) == NULL)
    {
        sum_of_errors |= STACK_DATA_NULL;
    }
    if ((stack->size) > (stack->capacity))
    {
        sum_of_errors |= BAD_POINTER;
    }
    if ((stack->size) == size_destroyed_stk) 
    {
        sum_of_errors |= STACK_DELETED;
    }
    if ((stack->RIGHT_MASTER) != RIGHT_CANARY)
    {
        sum_of_errors |= DAMAGED_RIGHT_CANARY;
    }
    if ((stack->LEFT_MASTER) != LEFT_CANARY)
    {
        sum_of_errors |= DAMAGED_LEFT_CANARY;
    }
    if ((*(CANARY_TYPE*)(stack->data - sizeof(CANARY_TYPE) / sizeof(elem_t))) != LEFT_DATA_CANARY)
    {
        sum_of_errors |= DAMAGED_LEFT_DATA_CANARY;
    }
    if ((*(CANARY_TYPE*)(stack->data + stack->capacity)) != RIGHT_DATA_CANARY)
    {
        sum_of_errors |= DAMAGED_RIGHT_DATA_CANARY;
    }
    // TODO compare haches
    return sum_of_errors; 
}

//===========================================================================

int stackDump(stack_type* stack, int* err, const char* name, const int line, const char* function, const char* file)
{
    FILE* fp = fopen("log.txt", "w");
    fprintf(fp, "capacity = %ld\n", stack->capacity);
    fprintf(fp, "size = %ld\n", stack->size);
    #ifdef VAR_INFO
        fprintf(fp, "stack has been called from: ");
        fprintf(fp, "line : %d, ", line);
        fprintf(fp, "function : %s, ", function);
        fprintf(fp, "file : %s, ", file);
        fprintf(fp, "name : %s, \n", name);
    #endif
    if (err != NULL)
    {
        fprintf(fp, "size when pop 0: %d \n", ZERO_ELEM_POP);
    }
    if (stack->error == STACK_OK)
    {
        fprintf(fp, "all is ok\n");
    }
   
    else
    {
        for (size_t i = 0; i < (stack->capacity); i++)
        {
            fprintf(fp, "data[%ld] = %d\n", i, stack->data[i]);
        }
        fprintf(fp, "%d\n", stack->error);
        if (((stack->error) & STACK_NULL) == STACK_NULL)
        {
            fprintf(fp, "your stack hasn't been created yet\n");
        } 
        if (((stack->error) & STACK_DATA_NULL) == STACK_DATA_NULL)
        {
            fprintf(fp, "your stack data has NULL pointer\n");
        } 
        if (((stack->error) & BAD_POINTER) == BAD_POINTER)
        {
            fprintf(fp, "size > capacity\n");
        } 
        if (((stack->error) & STACK_DELETED) == STACK_DELETED)
        {
            fprintf(fp, "your stack hasn been already deleted\n");
        } 
        if (((stack->error) & DAMAGED_RIGHT_CANARY) == DAMAGED_RIGHT_CANARY)
        {
            fprintf(fp, "your stack has been hacked(right canary has been damaged)\n");
        } 
        if (((stack->error) & DAMAGED_LEFT_CANARY) == DAMAGED_LEFT_CANARY)
        {
            fprintf(fp, "your stack has been hacked(left canary has been damaged)\n");
            
        } 
        if (((stack->error) & DAMAGED_LEFT_DATA_CANARY) == DAMAGED_LEFT_DATA_CANARY)
        {
            fprintf(fp, "your stack has been hacked(left data canary has been damaged)\n");
        } 
        if (((stack->error) & DAMAGED_RIGHT_DATA_CANARY) == DAMAGED_RIGHT_DATA_CANARY)
        {
            fprintf(fp, "your stack has been hacked(right data canary has been damaged)\n");
        } 
    }
      for (size_t i = 0; i < (stack->capacity); i++)
        {
            fprintf(fp, "data[%ld] = %d\n", i, stack->data[i]);
        }
    fclose(fp);
    stack->error = stackError(stack);
    return stack->error;
}
#endif

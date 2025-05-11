# STACK 
## FIFO and secure structure
This stack has high secure level, the stack structure looks common like array's structure:
```
typedef struct stack_type 
{
    CANARY_TYPE LEFT_MASTER;
    elem_t* data;
    size_t size;
    size_t capacity;
    ...
    CANARY_TYPE RIGHT_MASTER;  
} stack_type;
```
**BUT** there is an addition:
- LEFT_MASTER is a left canary
- RIGHT_MASTER is a right canary 
- also there are two canaries in the array data in the beginning and in the end

This canaries can't change their value, so if you are doing some operations with stack, the canaries are being checked every time

There is a dump file in the project, that is being dumped every execution. Example of dump is in log.txt 

### The project was done in the october of 2022

### Refactored in may 2025
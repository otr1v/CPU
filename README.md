# This is my first big project named CPU
# Program can read some commands (full list of commands in  cmd.h) - assembler, and then CPU does this commands using stack
# Program can count factorial and solve quadratic equation(only with integer solves)
 MAX_LABEL_SIZE = 300 - max number that can have your label
 MAX_COMMANDS = 1000 - max size of array code
 AMOUNT_OF_REGISTERS = 20 - max amount of registers
 AMOUNT_OF_RAM  = 15 - ram has only 15 places where you can write your numbers
 Attention: in code i have only 6 registers: rax, rbx, rcx, rdx, rex and rfx. You can add more.
 There is always a question, how user can add a new command?
 It is so easy to do:
 name of your command  number of cmd in order amount of args(0 or 1)
 
 In cmd.h type DEF_CMD(name, num, arg, code)
 1. name of your command 2. number of cmd in order 3. amount of args(0 or 1) 4. code of your command

## All commands that i have:
## push:
 push rax  - push register to stack
 push [10] - push RAM element to stack
 push 5    - push a number to stack
## pop:
 pop rax - pops the last element of stack to register
## jumps: (for conditions and cycle)
 jb <
 jbe <=
 ja >
 jae >=
 je =
 jne ==
## operations in stack:
 add - pops two elements from stack and add up
 mul - pops two elements from stack and multiply them
 sub - pops two elements from stack and substitute them
 div - pops two elements from stack and divide them
 endl - prints '\n'
 prnt - prints '0'
 space - prints ' '
 hlt - ends the program
 sqrt - takes square root from the last number in stack
 cpy - copies the last element from stack

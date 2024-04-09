# This is my first big project named CPU
## Program can read some commands (full list of commands in  cmd.h) - assembler, and then CPU does this commands using stack
## Program can count factorial and solve quadratic equation(only with integer solves)
 MAX_LABEL_SIZE = 300 - max number that can have your label <br/>
 MAX_COMMANDS = 1000 - max size of array code <br/>
 AMOUNT_OF_REGISTERS = 20 - max amount of registers <br/>
 AMOUNT_OF_RAM  = 15 - ram has only 15 places where you can write your numbers <br/>
 Attention: in code i have only 6 registers: rax, rbx, rcx, rdx, rex and rfx. You can add more. <br/>
 ## There is always a question, how user can add a new command? <br/>
 It is so easy to do: <br/>
 name of your command  number of cmd in order amount of args(0 or 1) <br/>
 
 In cmd.h type DEF_CMD(name, num, arg, code) <br/>
 1. name of your command 2. number of cmd in order 3. amount of args(0 or 1) 4. code of your command <br/>

## All commands that i have:
## push:
 push rax  - push register to stack <br/>
 push [10] - push RAM element to stack <br/>
 push 5    - push a number to stack <br/>
## pop:
 pop rax - pops the last element of stack to register <br/>
## jumps: (for conditions and cycle)
 jb < <br/>
 jbe <= <br/>
 ja > <br/>
 jae >= <br/>
 je = <br/>
 jne == <br/>
## operations in stack:
 add - pops two elements from stack and add up <br/>
 mul - pops two elements from stack and multiply them <br/>
 sub - pops two elements from stack and substitute them <br/>
 div - pops two elements from stack and divide them <br/>
 endl - prints '\n' <br/>
 prnt - prints '0' <br/>
 space - prints ' ' <br/>
 hlt - ends the program <br/>
 sqrt - takes square root from the last number in stack <br/>
 cpy - copies the last element from stack <br/>

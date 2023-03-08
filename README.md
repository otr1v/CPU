# This is my first big project named CPU
## It can read some command (full list of commands in  cmd.h) - assembler, and then CPU does this commands using stack
## It can count factorial and solve quadratic equation(only with integer solves)
### MAX_LABEL_SIZE = 300 - max number that can have your label
### MAX_COMMANDS = 1000 - max size of array code
### AMOUNT_OF_REGISTERS = 20 - max amount of registers
### AMOUNT_OF_RAM  = 15 - ram has only 15 places where you can write your numbers

#### There is always a question, how user can add a new command?
#### It is so easy to do:
#### name of your command  number of cmd in order amount of args(0 or 1)
#### 
#### In cmd.h type DEF_CMD(name, num, arg, code)
#### 1. name of your command 2. number of cmd in order 3. amount of args(0 or 1) 4. code of your command

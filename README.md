# CPU — My First Big Project

## Description
This program simulates a basic CPU that reads and executes a custom assembly-like language. It works via a stack-based model.

The program can:
- Read and interpret commands listed in `cmd.h`
- Calculate factorials
- Solve quadratic equations (integer roots only)

---

## How to build:
```
make asm
./asm.out <filename>
make my_cpu
./cpu.out out.bin
make dis_asm
./disasm 
```



###  Configuration
- `MAX_LABEL_SIZE = 300` — max label length
- `MAX_COMMANDS = 1000` — max size of the code array
- `AMOUNT_OF_REGISTERS = 20` — total available registers
- `AMOUNT_OF_RAM = 15` — available memory slots (RAM[0] to RAM[14])

**Note:** Currently, only 6 registers are implemented:
```
rax, rbx, rcx, rdx, rex, rfx
```
You can expand this set if needed.

---

## Adding a New Command
Adding new commands is easy! You just need to use the `DEF_CMD` macro in `cmd.h`:

```c
DEF_CMD(name, num, arg, code)
```
Where:
- `name` — name of the command (used in assembler input)
- `num` — unique command number (opcode)
- `arg` — number of arguments (0 or 1)
- `code` — the C code that implements the behavior

 **Example:**
```c
DEF_CMD(push, 1, 1,
    {
        val = GetArgs(&ip, cpu);
        stackPush(&(cpu->stack), &val);
    }
```

---

## Supported Commands

### PUSH
- `push rax` — push value of `rax` to stack
- `push [10]` — push value at RAM[10] to stack
- `push 5` — push immediate value `5`

### POP
- `pop rax` — pop top value from stack into `rax`

### Jumps (for conditions and loops)
- `jb` — jump if below (`<`)
- `jbe` — jump if below or equal (`<=`)
- `ja` — jump if above (`>`)
- `jae` — jump if above or equal (`>=`)
- `je` — jump if equal (`=`)
- `jne` — jump if not equal (`!=`)

### Stack Arithmetic
- `add` — add top two values
- `sub` — subtract top from second
- `mul` — multiply top two values
- `div` — divide second by top

### Other Commands
- `endl` — print newline (`\n`)
- `space` — print space character
- `prnt` — print zero (`0`)
- `hlt` — halt program
- `sqrt` — replace top with its square root
- `cpy` — duplicate top stack value

---

## Notes
- All arithmetic and operations are stack-based.
- Jumps rely on flags and comparison results set during execution.
- You can expand this architecture by adding your own instructions.

---

Made with ❤️ for low-level fun!



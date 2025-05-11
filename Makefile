INCLUDE_DIRS = -I -Icpu -Imy_stack -Iasm -Idisasm -Icommands
CFLAGS = -Wall -Wextra -Werror $(INCLUDE_DIRS)

asm:
	g++ asm/asm.cpp commands/filesize.cpp  $(CFLAGS) -o asm.out
my_cpu:
	g++ cpu/cpu.cpp commands/filesize.cpp $(CFLAGS) -o cpu.out
debug_asm:
	g++ asm/asm.cpp commands/filesize.cpp -g $(CFLAGS) -o  asm_debug.out
debug_cpu:
	g++ cpu/cpu.cpp commands/filesize.cpp -g $(CFLAGS) -o cpu_debug.out
disasm:
	g++ disasm/disasm.cpp commands/filesize.cpp $(CFLAGS) -o disasm.out
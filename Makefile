INCLUDE_DIRS = -I -Icpu -Istack -Iasm -Idisasm
CFLAGS = -Wall -Wextra -Werror $(INCLUDE_DIRS)

all:
	g++ asm.cpp filesize.cpp -o $(CFLAGS) asm
debug:
	g++ asm.cpp filesize.cpp -o -g $(CFLAGS) asm
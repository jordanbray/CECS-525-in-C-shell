CC=m68k-elf-gcc
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
AS=m68k-elf-as
OBJCOPY=m68k-elf-objcopy
QEMU=/opt/m68k/bin/qemu-system-m68k

CFLAGS=-nostdlib -nostartfiles -nodefaultlibs
CFLAGS+=-m68000
CFLAGS+=-Os
CFLAGS+=-I.

main: main.o iv.o screen.o exception.o kmem.o string.o tree.o shell.o linker.x
	${LD} main.o iv.o screen.o exception.o kmem.o string.o tree.o shell.o -o main -T linker.x -Map main.map
	cp main attach_gdb_to_this
	${OBJCOPY} -O srec main

main.o: main.c *.h
	${CC} ${CFLAGS} -c main.c -o main.o
	
tree.o:	string.h tree.h tree.c kmem.h
	${CC} ${CFLAGS} -c tree.c -o tree.o

string.o: string.h string.c
	${CC} ${CFLAGS} -c string.c -o string.o

shell.o: shell.h shell.c string.h screen.h
	${CC} ${CFLAGS} -c shell.c -o shell.o

iv.o: iv.asm
	${AS} -o iv.o iv.asm

screen.o: screen.h screen.c
	${CC} ${CFLAGS} -o screen.o -c screen.c

exception.o: exception.c
	${CC} ${CFLAGS} -o exception.o -c exception.c

kmem.o: kmem.h kmem.c
	${CC} -o kmem.o -c kmem.c

disassemble: main
	${OBJDUMP} -D attach_gdb_to_this

run: main
	${QEMU} -M cecs -nographic -kernel main -gdb tcp::1234

debug: main
	${QEMU} -M cecs -nographic -kernel main -S -gdb tcp::1234

clean:
	rm screen.o iv.o attach_gdb_to_this main main.o kmem.o main.map string.o tree.o shell.o

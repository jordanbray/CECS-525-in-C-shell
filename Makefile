CC=m68k-elf-gcc
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
AS=m68k-elf-as
OBJCOPY=m68k-elf-objcopy
QEMU=/opt/m68k/bin/qemu-system-m68k

CFLAGS=-nostdlib -nostartfiles -nodefaultlibs
CFLAGS+=-m68000
CFLAGS+=-Os

main: assembly.o iv.o screen.o main.o exception.o linker.x kmem.o
	${LD} main.o assembly.o iv.o screen.o exception.o kmem.o -o main -T linker.x -Map main.map
	cp main attach_gdb_to_this
	${OBJCOPY} -O srec main

disassemble: main
	${OBJDUMP} -D attach_gdb_to_this

iv.o: iv.asm
	${AS} -o iv.o iv.asm

main.o: main.c
	${CC} ${CFLAGS} -c main.c -o main.o

assembly.o: assembly.h assembly.c
	${CC} ${CFLAGS} -o assembly.o -c assembly.c

screen.o: screen.h screen.c assembly.h
	${CC} ${CFLAGS} -o screen.o -c screen.c

exception.o: exception.c
	${CC} ${CFLAGS} -o exception.o -c exception.c

kmem.o: kmem.h kmem.c
	${CC} -o kmem.o -c kmem.c

run: main
	${QEMU} -M cecs -nographic -kernel main -gdb tcp::1234

debug: main
	${QEMU} -M cecs -nographic -kernel main -S -gdb tcp::1234

clean:
	rm assembly.o screen.o iv.o attach_gdb_to_this main main.o kmem.o main.map


CC=m68k-elf-gcc
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
AS=m68k-elf-as
OBJCOPY=m68k-elf-objcopy
QEMU=/opt/m68k/bin/qemu-system-m68k

main: assembly.o iv.o screen.o main.o kmem.o
	${LD} main.o assembly.o iv.o screen.o kmem.o -o main -Ttext 0x0200 -Tdata 0
	cp main attach_gdb_to_this
	${OBJCOPY} -O srec main

disassemble: main
	${OBJDUMP} -D attach_gdb_to_this

iv.o: iv.asm
	${AS} -o iv.o iv.asm

main.o: main.c
	${CC} -c main.c -nostdlib -nostartfiles -nodefaultlibs -o main.o

assembly.o: assembly.h assembly.c
	${CC} -o assembly.o -c assembly.c

screen.o: screen.h screen.c assembly.h
	${CC} -o screen.o -c screen.c

kmem.o: kmem.h kmem.c
	${CC} -o kmem.o -c kmem.c

run: main
	${QEMU} -M cecs -nographic -kernel main -gdb tcp::1234

debug: main
	${QEMU} -M cecs -nographic -kernel main -S -gdb tcp::1234

clean:
	rm assembly.o screen.o iv.o attach_gdb_to_this main main.o kmem.o


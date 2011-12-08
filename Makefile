# config options
CC=m68k-elf-gcc
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
AS=m68k-elf-as
OBJCOPY=m68k-elf-objcopy
QEMU=/opt/m68k/bin/qemu-system-m68k

# don't touch these...
CFLAGS=-nostdlib -nostartfiles -nodefaultlibs --no-builtin
CFLAGS+=-m68000
CFLAGS+=-Os
CFLAGS+=-I.
KERNEL_SRCS=$(wildcard *.c)
KERNEL_OBJS=$(patsubst %.c,%.o,$(KERNEL_SRCS))
AUTH_SRCS=$(wildcard auth/*.c)
AUTH_OBJS=$(patsubst auth/%.c,auth/%.o,$(AUTH_SRCS))
CMD_SRCS=$(wildcard commands/*.c)
CMD_OBJS=$(patsubst commands/%.c,commands/%.o,$(CMD_SRCS))
CRYPT_SRCS=$(wildcard crypto/*.c)
CRYPT_OBJS=$(patsubst crypto/%.c,crypto/%.o,$(CRYPT_SRCS))

# code
main: linker.x iv.o $(KERNEL_OBJS) $(CRYPT_OBJS) $(AUTH_OBJS) $(CMD_OBJS)
	${LD} $(KERNEL_OBJS) $(CRYPT_OBJS) $(AUTH_OBJS) $(CMD_OBJS) iv.o -o main -T linker.x -Map main.map
	cp main attach_gdb_to_this
	${OBJCOPY} -O srec main

iv.o: iv.asm
	${AS} -o iv.o iv.asm

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $^

auth/%.o: auth/%.c
	${CC} ${CFLAGS} -o $@ -c $^

commands/%.o: commands/%.c
	${CC} ${CFLAGS} -o $@ -c $^

crypto/%.o: crypto/%.c
	${CC} ${CFLAGS} -o $@ -c $^

# commands
disassemble: main
	${OBJDUMP} -D attach_gdb_to_this

run: main
	${QEMU} -M cecs -nographic -kernel main -gdb tcp::1234

debug: main
	${QEMU} -M cecs -nographic -kernel main -S -gdb tcp::1234

clean:
	-rm attach_gdb_to_this main main.map *.o commands/*.o crypto/*.o auth/*.o

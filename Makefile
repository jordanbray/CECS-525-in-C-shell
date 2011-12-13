# config options
CC=m68k-elf-gcc
LD=m68k-elf-ld
OBJDUMP=m68k-elf-objdump
AS=m68k-elf-as
OBJCOPY=m68k-elf-objcopy
#QEMU=/opt/m68k/bin/qemu-system-m68k
QEMU="/cygdrive/c/Program Files/Qemu/qemu-system-m68k.exe"

# don't touch these...
CFLAGS=-nostdinc -nostdlib -ffreestanding -nostartfiles -nodefaultlibs
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
main.srec: linker.x iv.o $(KERNEL_OBJS) $(CRYPT_OBJS) $(AUTH_OBJS) $(CMD_OBJS)
	${LD} $(KERNEL_OBJS) $(CRYPT_OBJS) $(AUTH_OBJS) $(CMD_OBJS) iv.o -o main.srec -T linker.x -Map main.map
	cp main.srec attach_gdb_to_this
	${OBJCOPY} -O srec main.srec

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
disassemble: main.srec
	${OBJDUMP} -D attach_gdb_to_this

run: main.srec
	${QEMU} -M cecs -nographic -kernel main.srec -serial mon:telnet:127.0.0.1:4444,server,nowait -gdb tcp:127.0.0.1:1234

connect: main.srec
	telnet 127.0.0.1 4444

debug: main.srec
	${QEMU} -M cecs -nographic -kernel main.srec -serial mon:telnet:127.0.0.1:4444,server,nowait -S -gdb tcp:127.0.0.1:1234
	
gdb: main.srec
	./run_gdb

clean:
	-rm attach_gdb_to_this main.srec main.map *.o commands/*.o crypto/*.o auth/*.o

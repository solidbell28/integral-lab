CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

.PHONY: all

all: integral

integral: main.o integral.o funcs.o
	$(CC) $^ -o $@ $(LDLIBS)

funcs.o: funcs.asm
	nasm -f elf32 $< -o $@

integral.o: integral.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main.o integral.o funcs.o integral

test:
	./integral -R 4:5:0.0:1.2:0.0001:1.0
	./integral -R 4:6:0.0:2.0:0.0001:1.0
	./integral -R 5:6:0.0:2.0:0.0001:1.0
	./integral -I 4:0.0:3.0:0.0001:3.0
	./integral -I 5:5.0:6.0:0.0001:43.75
	./integral -I 6:10.0:15.0:0.0001:-120.0

CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic
LDLIBS=-lpthread -lrt
TARGET=proj2

CFLAGS+=-O2
#################################

all: $(TARGET)

$(TARGET): main.o santa_task.o rendeer_task.o elf_task.o base.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

#################################

.PHONY: pack clean run all

pack:
	zip proj2 *.h *.c Makefile

clean:
	rm -f $(TARGET) $(LIBRARY) *.o $(TARGET).out

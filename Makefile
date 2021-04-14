CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic
LDLIBS=-lpthread
TARGET=proj2
CFLAGS+=-g

#################################

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $@ $^

#################################

.PHONY: zip clean run all

zip:
	zip proj2 *.h *.c Makefile

clean:
	rm -f $(TARGET) *.o

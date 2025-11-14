CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2 -std=c11

SRC = src/keymanager.c src/xor.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = fulltest

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

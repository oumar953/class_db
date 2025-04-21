#makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC = src
DB_SRCS = $(SRC)/database.c $(SRC)/btree.c
MAIN_SRCS = $(SRC)/main.c $(DB_SRCS)
TARGET = db

all: $(TARGET)

$(TARGET): $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

test: tests/test_db.c $(DB_SRCS)
	$(CC) $(CFLAGS) -o test_db $^
	./test_db

clean:
	rm -f $(TARGET) test_db

.PHONY: all test clean

# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC = src
SRCS = $(SRC)/main.c $(SRC)/database.c $(SRC)/btree.c
TARGET = db

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

test: tests/test_db.c $(SRCS)
	$(CC) $(CFLAGS) -o test_db tests/test_db.c $(SRCS)

clean:
	rm -f $(TARGET) test_db

.PHONY: all test clean


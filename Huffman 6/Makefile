ASG_NICKNAME = HW20
BASE_NAME = huffman
EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov
TEST_C = $(EXECUTABLE).c
SRC_C = $(BASE_NAME).c priority_queue.c frequencies.c bit_writer.c
ADD_H = log_macros.h miniunit.h
SRC_H = $(BASE_NAME).h $(ADD_H) priority_queue.h frequencies.h bit_writer.h
SUBMIT_FILES = $(SRC_C) $(SRC_H) $(TEST_C) Makefile
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

pretest: submit
	264test $(ASG_NICKNAME)

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

.PHONY: submit test pretest clean coverage

CC = gcc
CFLAGS = -O0 -pipe -Wall -Werror -Wextra -g 
LDLIBS ?=

all: receiver-tcp sender-tcp

receiver-tcp: src/receiver-tcp.c
	gcc -o bin/receiver-tcp src/receiver-tcp.c

sender-tcp: src/sender-tcp.c
	gcc -o bin/sender-tcp src/sender-tcp.c

	@echo "\033[92mCompiled\033[0m"

.PHONY: clean
clean:
	rm -rf build/*.o
	rm -rf bin/*
	@echo "\033[92mCleaned\033[0m"
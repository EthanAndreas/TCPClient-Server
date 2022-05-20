CC = gcc
CFLAGS = -O0 -pipe -Wall -Werror -Wextra -g 
LDLIBS ?=

all: receiver-unique sender-unique receiver-multi sender-multi

receiver-unique: src/receiver-unique.c
	gcc -o bin/receiver-unique src/receiver-unique.c

sender-unique: src/sender-unique.c
	gcc -o bin/sender-unique src/sender-unique.c

receiver-multi: src/receiver-multi.c
	gcc -o bin/receiver-multi src/receiver-multi.c

sender-multi: src/sender-multi.c
	gcc -o bin/sender-multi src/sender-multi.c

	@echo "\033[92mCompiled\033[0m"

.PHONY: clean
clean:
	rm -rf build/*.o
	rm -rf bin/*
	@echo "\033[92mCleaned\033[0m"
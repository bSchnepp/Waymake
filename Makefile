#Makefile for a make system!

CC = clang
CFLAGS = -std=c11 -O3
NAME = waymake

all: createbuildir
	$(CC) $(CFLAGS) $(NAME).c -o build/$(NAME)

createbuildir:
	mkdir build

clean:
	rm -rf build/

install: all
	cp build/$(NAME) /bin/

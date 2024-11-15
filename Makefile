CC=$(clang)

build:
	- mkdir out
	clang -o out/main src/*.c -lncurses

run:
	./out/main

all:
	make build 
	make run


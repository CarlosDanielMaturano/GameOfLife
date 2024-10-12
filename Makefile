CC=$(clang)

build:
	- mkdir out
	clang -o out/main src/*.c 

run:
	./out/main

all:
	make build 
	make run


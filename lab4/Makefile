files =
build:
	gcc -c func.c
	gcc -o main main.c
test: build
	gcc -o test test.c
	./test
main: build test
	./main $(files)
clean:
	rm -f func.o main test func
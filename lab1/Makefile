test:
	gcc -c func.c
	gcc -o tests tests.c
	./tests
main: test
	gcc -o main main.c
	./main
clean:
	rm -f func.o main tests

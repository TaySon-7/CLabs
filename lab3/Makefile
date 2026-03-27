test:
	gcc -c func.c
	gcc -o tests test.c
	./tests
main:  test
	gcc -o main main.c
	./main
clean:
	rm -f func.o main tests func

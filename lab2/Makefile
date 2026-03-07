test:
	gcc -c func.c
	gcc -o tests tests.c
	./tests
main: generate test
	gcc -o main main.c
	./main
clean:
	rm -f func.o main tests generator func
generate:
	gcc -o generator generator.c
	./generator

all:main

main : main.o
	g++ -o main  main.o
main.o : main.c
	g++ -c main.c	

clean:
	rm -rf *.o *~ main
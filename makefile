coloGraph.exe: coloGraph.o
	gcc -o coloGraph.exe coloGraph.o

coloGraph.o: coloGraph.c 
	gcc -c coloGraph.c

clean:
	rm *.o
	rm *.exe

all: clean coloGraph.exe 




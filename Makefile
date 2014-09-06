PROGRAMS= gtthread.a diningPhilosopher
all: $(PROGRAMS)

clean:
	$(RM) *.o $(PROGRAMS) &> /dev/null || true
	
debug: clean
	make "CC=gcc -g -Wall -pedantic -DLF_DEBUG"
	
gtthread.a:
	gcc -c -o gtthread.a gtthread.c


diningPhilosopher: gtthread.a dp_gt.o
	gcc -Wall -pedantic gtthread.a dp_gt.o -o diningPhilosopher


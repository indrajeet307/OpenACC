COMPILER=pgcc
DEBUGFLAG=-g
PGIFLAGS=-Minfo -acc 
PROFFLAGS=-pg
all: matmul
	./matmul.out

matmul: matmul.c
	$(COMPILER) $(DEBUGFLAG) $(PGIFLAGS) $(PROFFLAGS) matmul.c -o matmul.out

prof: matmul
	nvprof ./matmul.out

clean:
	rm -f *.out *.s *.gpu *.o

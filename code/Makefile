COMPILER=pgcc
DEBUGFLAG=-g
PGIFLAGS=-Minfo -acc 
PROFFLAGS=-pg
all: vecadd matmul oddeven trial
vecadd: vecadd.c
	pgcc -g -Minfo -acc -pg vecadd.c -o vecadd.out
matmul: matmul.c
	pgcc -g -Minfo -acc -pg matmul.c -o matmul.out
oddeven: oddeven.c
	pgcc -g -Minfo -acc -pg oddeven.c -o oddeven.out
trial: Trial.c
	pgcc -g -Minfo -acc -pg Trial.c -o trial.out
clean:
	rm *.out

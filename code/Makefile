COMPILER=pgcc
DEBUGFLAG=-g
PGIFLAGS=-Minfo -acc 
PROFFLAGS=-pg
KEEPCUDAFLAG= -Mcuda=keepgpu
all: vecadd matmul oddeven trial
vecadd: vecadd.c
	$(COMPILER) $(DEBUGFLAG) $(PGIFLAGS) $(PROFFLAGS) vecadd.c -o vecadd.out
matmul: matmul.c
	$(COMPILER) $(DEBUGFLAG) $(PGIFLAGS) $(PROFFLAGS) matmul.c -o matmul.out
oddeven: oddeven.c
	$(COMPILER) $(DEBUGFLAG) $(PGIFLAGS) $(PROFFLAGS) $(KEEPCUDAFLAG) oddeven.c -o oddeven.out 
trial: Trial.c
	$(COMPILER) $(DEBUGFLAG) $(PGIFLAGS) $(PROFFLAGS) Trial.c -o trial.out
clean:
	rm -f *.out *.s *.gpu *.o

all: vecadd matmul oddeven
vecadd: vecadd.c
	pgcc -g -Minfo -acc -pg vecadd.c -o vecadd.out
matmul: matmul.c
	pgcc -g -Minfo -acc -pg matmul.c -o matmul.out
oddeven: oddeven.c
	pgcc -g -Minfo -acc -pg oddeven.c -o oddeven.out
clean:
	rm *.out

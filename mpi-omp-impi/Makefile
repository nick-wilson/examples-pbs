EXE = MPI-OpenMP

$(EXE).x: $(EXE).c
	mpiicc -qopenmp -O3 -xHost $^ -o $@

clean:
	rm -f $(EXE).x *.o

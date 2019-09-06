EXE = MPI

$(EXE).x: $(EXE).f
	mpiifort -O3 -xHost $^ -o $@

clean:
	rm -f $(EXE).x *.o

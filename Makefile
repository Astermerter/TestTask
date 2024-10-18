CC = g++
VC = iverilog
VVP = vvp
VFILES = main.v test.v

all: run_test_simulation

main: main.o sub.o
	$(CC) -o main main.o sub.o

main.o: main.cpp
	$(CC) -c main.cpp

sub.o: sub.cpp
	$(CC) -c sub.cpp

clean:
	rm *.o
	rm sim
	rm main

run_main: main
	@echo "Running the cpp program..."
	./main
	rm main
	rm *.o

create_simulation:run_main
	$(VC) $(VFILES) -o sim

run_test_simulation: create_simulation
	@echo "Running the test simulation..."
	$(VVP) sim
    	rm sim

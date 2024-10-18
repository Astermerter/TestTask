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
        rm -f *.o sim main

run_main: main
        @echo "Running the C++ program..."
        ./main
        rm -f main
        rm -f *.o

create_simulation: run_main
        @echo "Creating the Verilog simulation..."
        $(VC) $(VFILES) -o sim

run_test_simulation: create_simulation
        @echo "Running the Verilog test simulation..."
        $(VVP) sim
        @echo "Test simulation complete."
	rm -f sim

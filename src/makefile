all: simulator.o memory.o instruction.o global_vars.o
	g++ simulator.o memory.o instruction.o global_vars.o -o bin/simulator

simulator.o: simulator.cpp memory.hpp instruction.hpp constants.hpp global_vars.hpp
	g++ -c simulator.cpp

memory.o: memory.cpp memory.hpp instruction.hpp constants.hpp global_vars.hpp
	g++ -c memory.cpp
	
instruction.o: instruction.cpp instruction.hpp global_vars.hpp
	g++ -c instruction.cpp
	
global_vars.o: global_vars.cpp global_vars.hpp
	g++ -c global_vars.cpp
	
run: 
	bin/simulator sw_0a.bin
	
clean:
	rm -rf "*.o"
	
simulator:
	make all
	make run

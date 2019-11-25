simulator: src/simulator.o src/memory.o src/instruction.o src/global_vars.o
	mkdir -p bin
	g++ src/simulator.o src/memory.o src/instruction.o src/global_vars.o -o bin/mips_simulator

simulator.o: src/simulator.cpp src/memory.hpp src/instruction.hpp src/constants.hpp src/global_vars.hpp
	g++ -c src/simulator.cpp

memory.o: src/memory.cpp src/memory.hpp src/instruction.hpp src/constants.hpp src/global_vars.hpp
	g++ -c memory.cpp
	
instruction.o: src/instruction.cpp src/instruction.hpp src/global_vars.hpp
	g++ -c src/instruction.cpp
	
global_vars.o: src/global_vars.cpp src/global_vars.hpp
	g++ -c src/global_vars.cpp
	
clean:
	rm -rf src/"*.o"
	rm -rf bin/mips_simulator
	
testbench:
	#bash file already exists: bin/mips_testbench
	

	

	
	


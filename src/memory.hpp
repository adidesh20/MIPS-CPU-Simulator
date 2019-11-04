#ifndef MEMORY

#define MEMORY

#include <iostream>
#include <vector>
#include <string>

class memory
{
private:
	std::vector<uint8_t> ADDR_INSTR;
	
	//space for other memories to be defined in the future

public:
	memory(std::ifstream &bin);
};

#endif
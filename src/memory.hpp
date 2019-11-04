#ifndef MEMORY_HEAD

#define MEMORY_HEAD

#include <iostream>
#include <vector>
#include <string>
#include "constants.hpp"

class memory
{
private:
	std::vector<uint8_t> ADDR_INSTR;
	std::vector<uint8_t> ADDR_DATA;
	
	//space for other memories to be defined in the future

public:
	memory(std::ifstream &bin);
	
	int get_instr(int &pc, uint32_t& instr);
	
};

#endif
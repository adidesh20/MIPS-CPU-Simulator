#ifndef MEMORY_HEAD

#define MEMORY_HEAD

#include <iostream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "global_vars.hpp"

class memory
{
private:
	std::vector<uint8_t> ADDR_INSTR;
	std::vector<uint8_t> ADDR_DATA;
	//space for other memories to be defined in the future


	int end_index;

public:

	memory(std::ifstream &bin);
	void get_instr(uint32_t& instr);
	void get_byte(uint32_t address, int8_t& byte);
	void get_word(uint32_t address, uint32_t& word);
	void get_half_word(uint32_t address, int16_t& half_word);
	void put_byte(uint32_t address, int8_t& byte);
	void put_word(uint32_t address, uint32_t& word);
	void put_half_word(uint32_t address, int16_t& half_word);

};

#endif
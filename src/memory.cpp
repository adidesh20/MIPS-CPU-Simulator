#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "memory.hpp"
#include "constants.hpp"


memory::memory(std::ifstream &bin)
{
	bin.seekg(0, bin.end);
	int size = bin.tellg();
	bin.seekg(0);
	char buffer[size];
	bin.read(buffer, size);
	ADDR_INSTR.assign(INSTR_LENGTH, 0);
	ADDR_DATA.assign(DATA_LENGTH, 0);

	for (int i = 0; i < size / 8; i++)
	{
		std::string byte;
		for (int j = 0; j < 8; j++)
		{
			byte.push_back(buffer[j + (i * 8)]);
		}
		//std::cout << std::endl << byte << std::endl;
		uint8_t int_byte = std::stoi(byte, 0, 2);
		ADDR_INSTR[i] = int_byte;
		std::cerr << "Reached end" << std::endl;
	}
}

int  memory::get_instr(int &pc, uint32_t& instr)
{
	if (pc < INSTR_BASE || pc >= (INSTR_BASE + INSTR_LENGTH) || (pc % 0x4 != 0))
	{
		return(-11);
	}
	int index = pc - INSTR_BASE;

	instr = ADDR_INSTR[index] << 24;
	instr += ADDR_INSTR[index + 1] << 16;
	instr += ADDR_INSTR[index + 2] << 8;
	instr += ADDR_INSTR[index + 3];

}
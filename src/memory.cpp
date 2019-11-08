#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "memory.hpp"
#include "constants.hpp"
#include "global_vars.hpp"


memory::memory(std::ifstream &bin)
{
	bin.seekg(0, bin.end);
	int size = bin.tellg();
	bin.seekg(0);
	char buffer[size];
	//std::cout << size;
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
	}
	end_index = size / 8;
}

void  memory::get_instr(uint32_t& instr)
{
	if (pc < INSTR_BASE || pc >= (INSTR_BASE + INSTR_LENGTH) || (pc % 0x4 != 0))
	{
		std::exit(-11);
	}
	int index = pc - INSTR_BASE;

	instr = ADDR_INSTR[index] << 24;
	instr += ADDR_INSTR[index + 1] << 16;
	instr += ADDR_INSTR[index + 2] << 8;
	instr += ADDR_INSTR[index + 3];
	//std::cerr << instr <<std::endl;

}

void memory::get_byte(uint32_t address, uint8_t& byte)
{
	if (address < DATA_BASE || address >(DATA_BASE + DATA_LENGTH))
	{
		std::exit(-11);
	}
	else
	{
		uint32_t index = address - DATA_BASE;
		byte = ADDR_DATA[index];
	}
}

void memory::get_word(uint32_t address, uint32_t& word)
{
	if (address < DATA_BASE || address >=(DATA_BASE + DATA_LENGTH) || (address % 0x4 != 0))
	{
		std::exit(-11);
	}
	else
	{
		uint32_t index = address - DATA_BASE;
		word = ADDR_DATA[index] << 24;
		word += ADDR_DATA[index + 1] << 16;
		word += ADDR_DATA[index + 2] << 8;
		word += ADDR_DATA[index + 3];
	}
}

void memory::put_byte(uint32_t address, uint8_t& byte)
{
	if (address < DATA_BASE || address >(DATA_BASE + DATA_LENGTH))
	{
		std::exit(-11);
	}
	else
	{
		uint32_t index = address - DATA_BASE;
		ADDR_DATA[index] = byte;
	}
}

void memory::put_word(uint32_t address, uint32_t& word)
{
	if (address < DATA_BASE || address >= (DATA_BASE + DATA_LENGTH) || (address % 0x4 != 0))
	{
		std::exit(-11);
	}
	else
	{
		uint32_t index = address - DATA_BASE;
		ADDR_DATA[index] = word >> 24;
		uint32_t word_temp = word << 8;
		ADDR_DATA[index + 1] = word_temp >> 24;
		word_temp = word << 16;
		ADDR_DATA[index + 2] = word_temp >> 24;
		word_temp = word << 24;
		ADDR_DATA[index + 3] = word_temp >> 24;
	}

}

bool memory::end_check()
{
	int index = pc - INSTR_BASE;
	if (index == end_index)
	{
		return true;
	}
	else
	{
		return false;
	}
}
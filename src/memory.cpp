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
	char * buffer;
	buffer = new char[size];
	//std::cout << size;
	bin.read(buffer, size);
	ADDR_INSTR.assign(INSTR_LENGTH, 0);
	ADDR_DATA.assign(DATA_LENGTH, 0);


	for (int i = 0; i < size; i++)
	{
		ADDR_INSTR[i] = buffer[i];
	}
	/*for (int i = 0; i < size / 8; i++)
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
	end_index = size / 8;*/
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

void memory::get_byte(uint32_t address, int8_t& byte)
{
	if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
	{
		uint32_t index = address - DATA_BASE;
		byte = ADDR_DATA[index];
	}
	else if ((address >= GETC_BASE) && (address < (GETC_BASE + GETC_LENGTH)))
	{
		int8_t input = std::getchar();
		if (!std::cin.good())
		{
			std::exit(-21);
		}
		if (input == EOF || std::cin.eof())
		{
			byte = 0xF;
			return;
		}
		else
		{
			byte = input;
		}
	}
	else if ((address >= INSTR_BASE) && address < ((INSTR_BASE + INSTR_LENGTH)))
	{
		uint32_t index = address - INSTR_BASE;
		byte = ADDR_INSTR[index];
	}
	else
	{
		std::exit(-11);
	}
}

void memory::get_word(uint32_t address, uint32_t& word)
{
	if (address % 4 != 0)
	{
		std::exit(-11);
	}
	else if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
	{
		uint32_t index = address - DATA_BASE;
		word = ADDR_DATA[index] << 24;
		word += ADDR_DATA[index + 1] << 16;
		word += ADDR_DATA[index + 2] << 8;
		word += ADDR_DATA[index + 3];
	}
	else if (address == GETC_BASE)
	{
		int8_t input = std::getchar();
		if (!std::cin.good())
		{
			std::exit(-21);
		}
		if (input == EOF || std::cin.eof())
		{
			word = 0xFFFF;
			return;
		}
		else
		{
			word = input;
		}
	}
	else if ((address >= INSTR_BASE) && address < ((INSTR_BASE + INSTR_LENGTH)))
	{
		uint32_t index = address - INSTR_BASE;
		word = ADDR_INSTR[index] << 24;
		word += ADDR_INSTR[index + 1] << 16;
		word += ADDR_INSTR[index + 2] << 8;
		word += ADDR_INSTR[index + 3];
	}
	else
	{
		std::exit(-11);
	}
}

void memory::get_half_word(uint32_t address, int16_t & half_word)
{
	if (address % 2 != 0)
	{
		std::exit(-11);
	}
	else if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
	{
		uint32_t index = address - DATA_BASE;
		half_word = ADDR_DATA[index] << 8;
		half_word += ADDR_DATA[index + 1];
	}
	else if ((address >= GETC_BASE) && (address < (GETC_BASE + GETC_LENGTH)))
	{
		int8_t input = std::getchar();
		if (!std::cin.good())
		{
			std::exit(-21);
		}
		if (input == EOF || std::cin.eof())
		{
			half_word = 0xFF;
			return;
		}
		else
		{
			half_word = input;
		}
	}
	else if ((address >= INSTR_BASE) && address < ((INSTR_BASE + INSTR_LENGTH)))
	{
		uint32_t index = address - INSTR_BASE;
		half_word = ADDR_INSTR[index] << 8;
		half_word += ADDR_INSTR[index + 1];
	}
	else
	{
		std::exit(-11);
	}
}

void memory::put_byte(uint32_t address, int8_t& byte)
{
	if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
	{
		uint32_t index = address - DATA_BASE;
		ADDR_DATA[index] = byte;
	}
	else if ((address >= PUTC_BASE) && (address < (PUTC_BASE + PUTC_LENGTH)))
	{
		char out = byte;
		if (!std::cout.good())
		{
			std::exit(-21);
		}
		putchar(out);
	}
	else
	{
		std::exit(-11);
	}
}

void memory::put_word(uint32_t address, uint32_t& word)
{
	if (address % 4 != 0)
	{
		std::exit(-11);
	}
	else if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
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
	else if ((address >= PUTC_BASE) && (address < (PUTC_BASE + PUTC_LENGTH)))
	{
		int8_t out = (int8_t)(word & 0xFF);

		if (!std::cout.good())
		{
			std::exit(-21);
		}
		putchar(out);
	}
	else
	{
		std::exit(-11);
	}
}

void memory::put_half_word(uint32_t address, int16_t & half_word)
{
	if (address % 2 != 0)
	{
		std::exit(-11);
	}
	else if ((address >= DATA_BASE) && (address < DATA_BASE + DATA_LENGTH))
	{
		uint32_t index = address - DATA_BASE;
		ADDR_DATA[index] = half_word >> 8;
		uint16_t temp = half_word << 8;
		ADDR_DATA[index + 1] = temp >> 8;
	}
	else if ((address >= PUTC_BASE) && (address < (PUTC_BASE + PUTC_LENGTH)))
	{
		char out = (int8_t)(half_word & 0xFF);
		if (!std::cout.good())
		{
			std::exit(-21);
		}
		putchar(out);
	}
	else
	{
		std::exit(-11);
	}
}

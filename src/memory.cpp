#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include "memory.hpp"

memory::memory(std::ifstream &bin)
{
	bin.seekg(0, bin.end);
	int size = bin.tellg();
	bin.seekg(0);
	char buffer[size];
	bin.read(buffer, size);

	ADDR_INSTR.assign(0x1000000, 0);

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
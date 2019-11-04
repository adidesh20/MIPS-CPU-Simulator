#include <iostream>
#include<string>
#include <fstream>
#include <cstdlib>
#include "constants.hpp"
#include "memory.hpp"

char decode(uint32_t instruction, uint8_t& opcode);
void decode_r(uint32_t instruction, uint8_t& r_source1, uint8_t& r_source2, uint8_t& r_dest, uint8_t& r_shiftamt, uint8_t& r_fn);
void decode_j(uint32_t instruction, uint32_t& j_address);
void decode_i(uint32_t instruction, uint8_t& i_source1, uint8_t& i_dest, uint16_t& i_Astart);


int main(int argc, char *argv[])
{
	//READING AND STORING BINARY FILE
	if (argc > 1)
	{
		std::string binName = argv[1];
		std::cerr << binName << std::endl;
	}
	else
	{
		std::cout << "Binary not found" << std::endl;
		return(-21);
	}

	std::vector<uint32_t> registers;
	register.assign(32, 0);

	std::ifstream bin(argv[1], std::ios::in | std::ios::binary | std::ios::ate);


	if (!bin.is_open())
	{
		std::cout << "Could not open binary" << std::endl;
		return(-21);
	}
	else
	{
		std::cerr << "File was found!";

	}

	//reading the binary and storing in a vector
	//should happen in a memory class which will be written later
	bin.seekg(0, bin.end);
	int size = bin.tellg();
	bin.seekg(0);
	char buffer[size];
	bin.read(buffer, size);

	/*std::vector<uint8_t> ADDR_INSTR;
	ADDR_INSTR.assign(0x1000000, 0);

	for (int i = 0; i < size/8; i++)
	{
		std::string byte;
		for (int j = 0; j < 8; j++)
		{
			byte.push_back(buffer[j + (i * 8)]);
		}
		//std::cout << std::endl << byte << std::endl;
		uint8_t int_byte = std::stoi(byte, 0, 2);
		ADDR_INSTR[i] = int_byte;
	}*/

	int pc = 0x10000000;
	uint32_t instruction;
	uint8_t opcode;
	memory mips_mem(bin);
	mips_mem.get_instr(pc, instruction);
	std::cout << instruction << std::endl;
	char instr_type = decode(instruction);
	uint8_t r_source1;
	uint8_t r_source2;
	uint8_t r_dest;
	uint8_t r_shiftamt;
	uint8_t r_fn;
	uint8_t i_source1;
	uint8_t i_dest;
	uint16_t i_Astart;
	uint32_t j_address;

	if (instr_type == 'R')
	{
		decode_r(instruction, r_source1, r_source2, r_dest, r_shiftamt, r_fn);
	}
	else if(instr_type == 'J')
	{
		decode_j(instruction, j_address);
	}
	else if(instr_type == 'I')
	{
		decode_i(instruction, i_source1, i_dest, i_Astart);
	}


}

char decode(uint32_t instruction, uint8_t&opcode)
{
	opcode = instruction >> 26;

	if (opcode == 0)
	{
		return 'R';
	}
	else if (opcode == 2 || opcode == 3)
	{
		return 'J';
	}
	else
	{
		return 'I';
	}
}

void decode_r(uint32_t instruction, uint8_t& r_source1, uint8_t& r_source2, uint8_t& r_dest, uint8_t& r_shiftamt, uint8_t& r_fn)
{
	uint32_t instr_temp = instruction << 6;
	r_source1 = instr_temp >> 27;
	instr_temp = instruction << 11;
	r_source2 = instr_temp >> 27;
	instr_temp = instruction << 16;
	r_dest = instr_temp >> 27;
	instr_temp = instruction << 21;
	r_shiftamt = instr_temp >> 27;
	instr_temp = instruction << 26;
	r_fn = instr_temp >> 26;

	//std::cout << r_source1 << " " << r_source2 << " " << r_dest << " " << r_shiftamt << " " << r_fn;
}
void decode_j(uint32_t instruction, uint32_t& j_address)
{
	uint32_t instr_temp = instruction << 6;
	j_address = instr_temp >> 6;
	
	//std::cout << j_address;
}
void decode_i(uint32_t instruction, uint8_t& i_source1, uint8_t& i_dest, uint16_t& i_Astart)
{
	uint32_t instr_temp = instruction << 6;
	i_source1 = instr_temp >> 27;
	instr_temp = instruction << 11;
	i_dest = instr_temp >> 27;
	instr_temp = instruction << 16;
	i_Astart = instr_temp >> 16;

	//std::cout << i_source1 << std::endl << i_dest << std::endl << i_Astart;

}


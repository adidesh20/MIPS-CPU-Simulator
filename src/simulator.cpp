#include <iostream>
#include<string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "constants.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include "global_vars.hpp"
 
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
		std::exit(-21);
	}

	std::vector<int32_t> registers;
	registers.assign(32, 0);

	std::ifstream bin(argv[1], std::ios::in | std::ios::binary | std::ios::ate);


	if (!bin.is_open())
	{
		std::cerr << "Could not open binary" << std::endl;
		std::exit(-21);
	}
	else
	{
		std::cerr << "File was found!" << std::endl;

	}

	memory mips_mem(bin);
	while (pc != 0)
	{
		uint32_t instruction;
		mips_mem.get_instr(instruction);
		std::cout << instruction << std::endl;
		instruction_class mips_instr(instruction);
		mips_instr.decode();
		mips_instr.execute(registers, mips_mem);

		if (jump)
		{
			pc += 4;
			uint32_t extra_instruction;
			instruction_class extra(extra_instruction);
			extra.decode();
			extra.execute(registers, mips_mem);
			pc = jump_addr;
			jump = false;
		}
		else
		{
			pc += 4;
		}
		
		if (mips_mem.end_check())
		{
			pc = 0;
		}
	}
	int32_t r2 = registers[2] << 24;
	uint8_t ret = r2 >> 24;
	std::exit(ret);
	return 0;
}

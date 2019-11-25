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
		//std::cout << "Binary not found" << std::endl;
		std::exit(-21);
	}

	std::vector<int32_t> registers;
	registers.assign(32, 0);
	pc = INSTR_BASE;
	std::ifstream bin(argv[1], std::ios::in | std::ios::binary | std::ios::ate);


	if (!bin.is_open())
	{
		//std::cerr << "Could not open binary" << std::endl;
		std::exit(-20);
	}
	else
	{
		//std::cerr << "File was found!" << std::endl;

	}

	pc = INSTR_BASE;

	memory mips_mem(bin);
	uint32_t delay_instruction;
	instruction_class mips_delay;
	while (pc != 0)
	{
		uint32_t instruction;
		mips_mem.get_instr(instruction);
		instruction_class mips_instr(instruction);
		mips_instr.decode();
		mips_instr.execute(registers, mips_mem);
		pc += 4;
		if (jump)
		{
			if (jump_addr == 0)
			{
				int32_t r2 = registers[2] << 24;
				uint8_t ret = r2 >> 24;
				std::exit(ret);

			}
			jump = false;
			mips_mem.get_instr(delay_instruction);
			mips_delay.delayed_init(delay_instruction);
			mips_delay.decode();
			mips_delay.execute(registers, mips_mem);
			pc = jump_addr;
		}
	}

}

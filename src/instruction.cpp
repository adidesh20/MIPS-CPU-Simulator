#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "instruction.hpp"

instruction_class::instruction_class(uint32_t instr_in)
{
	instr = instr_in;
	opcode = instr_in >> 26;
	if (opcode == 0)
	{
		type = 'R';
	}
	else if (opcode == 2 || opcode == 3)
	{
		type = 'J';
	}
	else
	{
		type = 'I';
	}
}

void instruction_class::decode()
{
	if (type == 'R')
	{
		//call r 
		extract_r();

	}
	else if (type == 'J')
	{
		//call j 
		extract_j();
	}
	else if (type == 'I')
	{
		//call i 
		extract_i();
	}
	else
	{
		std::cout << "ERROR";
	}
}

void instruction_class::extract_r()
{
	uint32_t instr_temp = instr << 6;
	r_source1 = instr_temp >> 27;
	instr_temp = instr << 11;
	r_source2 = instr_temp >> 27;
	instr_temp = instr << 16;
	r_dest = instr_temp >> 27;
	instr_temp = instr << 21;
	r_shiftamt = instr_temp >> 27;
	instr_temp = instr << 26;
	r_fn = instr_temp >> 26;
}

void instruction_class::extract_j()
{
	uint32_t instr_temp = instr << 6;
	j_address = instr_temp >> 6;
}

void instruction_class::extract_i()
{
	uint32_t instr_temp = instr << 6;
	i_source1 = instr_temp >> 27;
	instr_temp = instr << 11;
	i_dest = instr_temp >> 27;
	instr_temp = instr << 16;
	i_Astart = instr_temp >> 16;
}

void instruction_class::look_up(std::vector<uint32_t> registers)
{
	if (type == 'R')
	{
		//call r 
		if (r_fn == 32) 
		{
			
			return add(registers);
		}
		

	}
	else if (type == 'J')
	{
		//call j 
		
	}
	else if (type == 'I')
	{
		//call i 
		
	}
	else
	{
		std::cout << "ERROR";
	}
}

void instruction_class::look_up_r()
{

}

void instruction_class::look_up_j()
{

}

void instruction_class::look_up_i()
{

}

void instruction_class::add(std::vector<uint32_t> registers)
{
	int source1;
	int source2;
	if (r_source1 == 1 && r_source2 == 2)
	{
		source1 = 1;
		source2 = 2;
	}
	
	std::cout << source1 << " + " << source2 << " = ";
	registers[r_dest] = registers[r_source1] + registers[r_source2];
	std::cout << registers[r_dest] << std::endl;
}
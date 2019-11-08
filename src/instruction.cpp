#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "instruction.hpp"
#include "global_vars.hpp"

//==========================CONSTRUCTOR==========================//
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

//==========================DATA EXTRACTION==========================//
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

//==========================EXECUTION==========================//
void instruction_class::execute(std::vector<int32_t>& registers, memory mips_mem, int& pc)
{
	if (type == 'R')
	{
		//call r 
		execute_r(std::vector<int32_t>& registers);
	}
	else if (type == 'J')
	{
		//call j 
		execute_j)();
	}
	else if (type == 'I')
	{
		//call i 
		execute_i();
	}
	else
	{
		std::cout << "ERROR";
	}
}

void instruction_class::execute_r(std::vector<int32_t>& registers)
{
	switch (r_fn)
	{
		case 33: addu(registers);
			break;
		case 32: add(registers);
			break;
	}
}

void instruction_class::execute_j(std::vector<int32_t>& registers)
{
	switch (opcode)
	{
		case 35: lw(registers, mips_mem);
			break;
		case 43: sw(registers, mips_mem);
			break;
	}
}

void instruction_class::execute_i(std::vector<int32_t>& registers)
{

}
//==========================R TYPE==========================//
void instruction_class::addu(std::vector<uint32_t>& registers)
{
	if (r_dest == 0) { return; }
	unsigned int source1 = r_source1;
	unsigned int source2 = r_source2;
	std::cerr << source1 << " + " << source2 << " = ";
	registers[r_dest] = source1 + source2;
	std::cerr << registers[r_dest] << std::endl;
}

void instruction_class::add(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	signed long long source1 = r_source1;
	signed long long source2 = r_source2;
	signed long long result = source1 + source2;
	result = result >> 32;
	if (result == 0)
	{
		std::cerr << source1 << " + " << source2 << " = ";
		registers[r_dest] = source1 + source2;
		std::cerr << registers[r_dest] << std::endl;
	}
	else
	{
		std::exit(10);
	}
}
void instruction_class::jr(std::vector<int32_t>& registers)
{
	jump = true;
	jump_addr = registers[j_address];
}


//==========================I TYPE==========================//
void instruction_class::lw(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	uint32_t address = registers[i_source1] + i_Astart;
	uint32_t word;
	mips_mem.get_word(address, word);
	registers[i_dest] = word;
}

void instruction_class::sw(std::vector<int32_t>& registers, memory mips_mem)
{
	uint32_t address = registers[i_source1] + i_Astart;;
	uint32_t word = registers[i_dest];
	mips_mem.put_word(address, word);
}

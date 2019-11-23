#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "instruction.hpp"
#include "global_vars.hpp"

//==========================CONSTRUCTORS==========================//


instruction_class::instruction_class()
{
	//here for the delay slot
}

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

void instruction_class::delayed_init(uint32_t instr_in)
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
	//std::cerr << "Entering Decode" << std::endl;
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
		//std::cerr << "Entered extract i" << std::endl;
		//call i 
		extract_i();
	}
	else
	{
		std::exit(-12);
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
	//std::cerr << "R Type Extracted" << std::endl;
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
	//std::cerr << "I Type Extracted" << std::endl;
}



//==========================EXECUTION==========================//
void instruction_class::execute(std::vector<int32_t>& registers, memory& mips_mem)
{
	//std::cerr << "Entering Execute" << std::endl;
	if (type == 'R')
	{
		//call r 
		execute_r(registers);
		return;
	}
	else if (type == 'J')
	{
		//call j 
		execute_j(registers, mips_mem);
		return;
	}
	else if (type == 'I')
	{
		//call i 
		execute_i(registers, mips_mem);
		return;
	}
	else
	{
		std::cout << "ERROR";
	}
}

void instruction_class::execute_r(std::vector<int32_t>& registers)
{
	//std::cerr << "Executing R Type" << std::endl;
	switch (r_fn)
	{
	case 0:
		sll(registers);
		break;
	case 2:
		srl(registers);
		break;
	case 3:
		sra(registers);
		break;
	case 4:
		sllv(registers);
		break;
	case 6:
		srlv(registers);
		break;
	case 7:
		srav(registers);
		break;
	case 8:
		jr(registers);
		break;
	case 9:
		jalr(registers);
		break;
	case 16:
		mfhi(registers);
		break;
	case 17:
		mthi(registers);
		break;
	case 18:
		mflo(registers);
		break;
	case 19:
		mtlo(registers);
		break;
	case 24:
		mult(registers);
		break;
	case 25:
		multu(registers);
		break;
	case 26:
		div(registers);
		break;
	case 27:
		divu(registers);
		break;
	case 32:
		add(registers);
		break;
	case 33:
		addu(registers);
		break;
	case 34:
		sub(registers);
		break;
	case 35:
		subu(registers);
		break;
	case 36:
		and_r(registers);
		break;
	case 37:
		or_r(registers);
		break;
	case 38:
		xor_r(registers);
		break;
	case 42:
		slt(registers);
		break;
	case 43:
		sltu(registers);
		break;
	default: std::cerr << "Default Path Taken";
		break;

	}
}

void instruction_class::execute_j(std::vector<int32_t>& registers, memory mips_mem)
{
	switch (opcode)
	{
	case 2:
		j();
		break;
	case 3:
		jal(registers);
	break;	default: std::cerr << "Default Path Taken";
	break;

	}
}

void instruction_class::execute_i(std::vector<int32_t>& registers, memory& mips_mem)
{
	//std::cerr << "Executing I Type" << std::endl;
	switch (opcode)
	{
	case 1:
		switch (i_dest)
		{
		case 0:
			bltz(registers);
			break;
		case 1:
			bgez(registers);
			break;
		case 16:
			bltzal(registers);
			break;
		case 17:
			bgezal(registers);
			break;
		}
		break;
	case 4:
		beq(registers);
		break;
	case 5:
		bne(registers);
		break;
	case 6:
		blez(registers);
		break;
	case 7:
		bgtz(registers);
		break;
	case 8:
		addi(registers);
		break;
	case 9:
		addiu(registers);
		break;
	case 10:
		slti(registers);
		break;
	case 11:
		sltiu(registers);
		break;
	case 12:
		andi(registers);
		break;
	case 13:
		ori(registers);
		break;
	case 14:
		xori(registers);
		break;
	case 15:
		lui(registers);
		break;
	case 32:
		lb(registers, mips_mem);
		break;
	case 33:
		lh(registers, mips_mem);
		break;
	case 34:
		lwl(registers, mips_mem);
		break;
	case 35:
		lw(registers, mips_mem);
		break;
	case 36:
		lbu(registers, mips_mem);
		break;
	case 37:
		lhu(registers, mips_mem);
		break;
	case 38:
		lwr(registers, mips_mem);
		break;
	case 40:
		sb(registers, mips_mem);
		break;
	case 41:
		sh(registers, mips_mem);
		break;
	case 43:
		sw(registers, mips_mem);
		break;
	default:
		std::cerr << "Default Path Taken";
		break;
	}
}
//==========================R TYPE==========================//
void instruction_class::addu(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }

	//std::cerr << registers[r_source1] << " + " << registers[r_source2] << " = ";
	registers[r_dest] = registers[r_source1] + registers[r_source2];
	//std::cerr << registers[r_dest] << std::endl;
}

void instruction_class::add(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	int32_t result = registers[r_source1] + registers[r_source2];
	if ((registers[r_source1] > 0) && (registers[r_source2] > 0) && (result <= 0)) {
		std::exit(-10);
	}
	else if ((registers[r_source1] < 0) && (registers[r_source2] < 0) && (result >= 0)) {
		std::exit(-10);
	}
	else {
		registers[r_dest] = result;

	}
}
void instruction_class::sub(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }
	int32_t result = registers[r_source1] - registers[r_source2];
	if (((registers[r_source1] >= 0) && (registers[r_source2] < 0) && (result < 0)) || ((registers[r_source1] < 0) && (registers[r_source2] >= 0) && (result >= 0))) {   //checks for overflow + underflow
		std::exit(-10);
	}
	else {
		registers[r_dest] = result;

	}
}
void instruction_class::subu(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	registers[r_dest] = registers[r_source1] - registers[r_source2];
}
void instruction_class::jr(std::vector<int32_t>& registers)
{
	jump = true;
	jump_addr = registers[r_source1];
}

void instruction_class::jalr(std::vector<int32_t>& registers)
{
	jump = true;
	jump_addr = registers[r_source1];
	if (r_dest == 0) { return; }
	else
	{
		registers[r_dest] = pc + 8;
	}
}

void instruction_class::and_r(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	else
	{
		registers[r_dest] = registers[r_source1] & registers[r_source2];
	}
}

void instruction_class::or_r(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	else
	{
		registers[r_dest] = registers[r_source1] | registers[r_source2];
	}
}

void instruction_class::xor_r(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	else
	{
		registers[r_dest] = registers[r_source1] ^ registers[r_source2];
	}
}



void instruction_class::div(std::vector<int32_t>& registers)
{
	int32_t numerator = registers[r_source1];
	int32_t denominator = registers[r_source2];
	if (registers[r_source2] != 0)
	{
		reg_hi = numerator % denominator;
		reg_lo = numerator / denominator;
	}
}

void instruction_class::divu(std::vector<int32_t>& registers)
{
	uint32_t numerator = registers[r_source1];
	uint32_t denominator = registers[r_source2];
	if (denominator != 0)
	{
		reg_hi = numerator % denominator;
		reg_lo = numerator / denominator;
	}
}

void instruction_class::mult(std::vector<int32_t>& registers)
{
	int64_t product = (int64_t)registers[r_source1] * (int64_t)registers[r_source2];
	reg_lo = (uint32_t)(product & 0xFFFFFFFF);
	reg_hi = (int32_t)(product >> 32 & 0xFFFFFFFF);
}

void instruction_class::multu(std::vector<int32_t>& registers)
{
	uint32_t ur_source1 = registers[r_source1];
	uint32_t ur_source2 = registers[r_source2];
	uint64_t product = (uint64_t)ur_source1 * (uint64_t)ur_source2;
	reg_lo = (uint32_t)(product & 0xFFFFFFFF);
	reg_hi = (uint32_t)(product >> 32 & 0xFFFFFFFF);
}

void instruction_class::sll(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	else
	{
		registers[r_dest] = registers[r_source2] << r_shiftamt;
	}
}


void instruction_class::sllv(std::vector<int32_t>& registers)
{
	int shift = registers[r_source1] & 0x1F;
	registers[r_dest] = registers[r_source2] << shift;
}

void instruction_class::srl(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }

	uint32_t source = registers[r_source2];
	int32_t shifted = source >> r_shiftamt;
	registers[r_dest] = shifted;
}

void instruction_class::srlv(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	int shift = registers[r_source1] & 0x1F;

	registers[r_dest] = registers[r_source2] >> shift;
}

void instruction_class::sra(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }

	registers[r_dest] = registers[r_source2] >> r_shiftamt;

}

void instruction_class::srav(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }
	int shift = registers[r_source1] & 0x1F;
	registers[r_dest] = registers[r_source2] >> shift;
}

void instruction_class::slt(std::vector<int32_t>& registers)
{
	if (registers[r_source1] < registers[r_source2])
	{
		registers[r_dest] = 1;
	}
	else
	{
		registers[r_dest] = 0;
	}
}

void instruction_class::sltu(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }
	uint32_t source1 = registers[r_source1];
	uint32_t source2 = registers[r_source2];

	if (source1 < source2)
	{
		registers[r_dest] = 1;
	}
	else
	{
		registers[r_dest] = 0;
	}
}

void instruction_class::mfhi(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }

	registers[r_dest] = reg_hi;
}

void instruction_class::mflo(std::vector<int32_t>& registers)
{
	if (r_dest == 0) { return; }

	registers[r_dest] = reg_lo;
}

void instruction_class::mthi(std::vector<int32_t>& registers)
{
	reg_hi = registers[r_source1];
}

void instruction_class::mtlo(std::vector<int32_t>& registers)
{
	reg_lo = registers[r_source1];
}



//==========================I TYPE==========================//
void instruction_class::addi(std::vector<int32_t>& registers)
{
	int16_t imm = i_Astart;
	int32_t result = registers[i_source1] + imm;
	if (i_dest == 0) { return; }
	if ((registers[i_source1] > 0) && (imm > 0) && (result <= 0)) {
		std::exit(-10);

	}
	else if ((registers[i_source1] < 0) && (imm < 0) && (result >= 0)) {
		std::exit(-10);
	}
	else {
		registers[i_dest] = result;
	}

}

void instruction_class::addiu(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	registers[i_dest] = registers[i_source1] + imm;
}

void instruction_class::andi(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }

	int32_t imm = i_Astart & 0x0000FFFF;// zero extend
	registers[i_dest] = registers[i_source1] & imm;
}

void instruction_class::lw(std::vector<int32_t>& registers, memory& mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	uint32_t word;
	mips_mem.get_word(address, word);
	registers[i_dest] = word;
}

void instruction_class::sw(std::vector<int32_t>& registers, memory& mips_mem)
{
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	uint32_t word = registers[i_dest];
	mips_mem.put_word(address, word);
}

void instruction_class::lui(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }
	uint32_t imm = i_Astart; //zero extension
	imm = imm << 16;
	registers[i_dest] = imm;
}
void instruction_class::ori(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }
	int32_t imm = i_Astart; //sign extension
	registers[i_dest] = registers[i_source1] | imm;
}

void instruction_class::lb(std::vector<int32_t>& registers, memory& mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int8_t byte;
	mips_mem.get_byte(address, byte);
	registers[i_dest] = (int32_t)byte;
}

void instruction_class::lbu(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int8_t byte;
	mips_mem.get_byte(address, byte);
	registers[i_dest] = (int32_t)byte;
	registers[i_dest] = registers[i_dest] & 0x000000FF;
}

void instruction_class::lh(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int16_t half_word;
	mips_mem.get_half_word(address, half_word);
	registers[i_dest] = int32_t(half_word);


}

void instruction_class::lhu(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int16_t half_word;
	mips_mem.get_half_word(address, half_word);
	registers[i_dest] = int32_t(half_word);
	registers[i_dest] = registers[i_dest] & 0x0000FFFF;
}

void instruction_class::lwl(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t eff_address = registers[i_source1] + imm;
	int no_MSB_bytes = 4 - eff_address % 4;
	uint32_t word;
	switch (no_MSB_bytes)

	{
	case 4:
		mips_mem.get_word(eff_address, word);
		registers[i_dest] = word;
		break;
	case 3:
		mips_mem.get_word(eff_address - 1, word);
		word = word << 8;
		registers[i_dest] = registers[i_dest] & 0xFF;
		registers[i_dest] += word;
		break;
	case 2:
		mips_mem.get_word(eff_address - 2, word);
		word = word << 16;
		registers[i_dest] = registers[i_dest] & 0xFFFF;
		registers[i_dest] += word;
		break;
	case 1:
		mips_mem.get_word(eff_address - 3, word);
		word = word << 24;
		registers[i_dest] = registers[i_dest] & 0xFFFFFF;
		registers[i_dest] += word;
		break;

	}
}

void instruction_class::lwr(std::vector<int32_t>& registers, memory mips_mem)
{
	if (i_dest == 0) { return; }
	int16_t imm = i_Astart;
	uint32_t eff_address = registers[i_source1] + imm;
	int no_LSB_bytes = (eff_address % 4) + 1;
	uint32_t word;
	switch (no_LSB_bytes)

	{
	case 4:
		mips_mem.get_word(eff_address - 3, word);
		registers[i_dest] = word;
		break;
	case 3:
		mips_mem.get_word(eff_address - 2, word);
		word = word >> 8;
		registers[i_dest] = registers[i_dest] & 0xFF000000;
		registers[i_dest] += word;
		break;
	case 2:
		mips_mem.get_word(eff_address - 1, word);
		word = word >> 16;
		registers[i_dest] = registers[i_dest] & 0xFFFF0000;
		registers[i_dest] += word;
		break;
	case 1:
		mips_mem.get_word(eff_address, word);
		word = word >> 24;
		registers[i_dest] = registers[i_dest] & 0xFFFFFF00;
		registers[i_dest] += word;
		break;

	}
}
void instruction_class::sb(std::vector<int32_t>& registers, memory& mips_mem)

{
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int8_t byte = (int8_t)(registers[i_dest] & 0xFF);
	mips_mem.put_byte(address, byte);
}

void instruction_class::sh(std::vector<int32_t>& registers, memory& mips_mem)
{
	int16_t imm = i_Astart;
	uint32_t address = registers[i_source1] + imm;
	int16_t half_word = (uint16_t)(registers[i_dest] & 0xFFFF);
	mips_mem.put_half_word(address, half_word);
}

void instruction_class::slti(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }

	int16_t imm = i_Astart;
	if (registers[i_source1] < imm)
	{
		registers[i_dest] = 1;
	}
	else
	{
		registers[i_dest] = 0;
	}
}

void instruction_class::sltiu(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }

	if ((uint32_t)registers[i_source1] < i_Astart)
	{
		registers[i_dest] = 1;
	}
	else
	{
		registers[i_dest] = 0;
	}
}

void instruction_class::xori(std::vector<int32_t>& registers)
{
	if (i_dest == 0) { return; }

	uint32_t imm = i_Astart;
	registers[i_dest] = registers[i_source1] ^ imm;
}

void instruction_class::beq(std::vector<int32_t>& registers)
{
	if (registers[i_source1] == registers[i_dest])
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
		}
	}
}

void instruction_class::bgez(std::vector<int32_t>& registers)
{
	if (registers[i_source1] >= 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
		}
	}
}

void instruction_class::bgezal(std::vector<int32_t>& registers)
{
	if (i_source1 == 31) { return; }
	registers[31] = pc + 8;

	if (registers[i_source1] >= 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;

		}
	}
}

void instruction_class::bgtz(std::vector<int32_t>& registers)
{
	if (registers[i_source1] > 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
		}
	}
}

void instruction_class::blez(std::vector<int32_t>& registers)
{
	if (registers[i_source1] <= 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
			registers[31] = pc + 8;
		}
	}
}

void instruction_class::bltz(std::vector<int32_t>& registers)
{
	if (registers[i_source1] < 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
			registers[31] = pc + 8;
		}
	}
}

void instruction_class::bltzal(std::vector<int32_t>& registers)
{
	if (i_source1 == 31) { return; }
	registers[31] = pc + 8;
	if (registers[i_source1] < 0)
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;

		}
	}
}

void instruction_class::bne(std::vector<int32_t>& registers)
{
	if (registers[i_source1] != registers[i_dest])
	{
		int16_t imm = i_Astart;
		int32_t imm32 = (int32_t)imm;
		uint32_t eff_addr = pc + 4 + (imm32 << 2);
		if ((eff_addr < INSTR_BASE || eff_addr >(INSTR_BASE + INSTR_LENGTH) || eff_addr % 4 != 0) && eff_addr != 0)
		{
			std::exit(-11);
		}
		else
		{
			jump = true;
			jump_addr = eff_addr;
			registers[31] = pc + 8;
		}
	}
}

void instruction_class::j()
{
	jump = true;
	uint32_t branch_delay = pc + 4;
	jump_addr = branch_delay & 0xF0000000;
	jump_addr += j_address << 2;
}

void instruction_class::jal(std::vector<int32_t>& registers)
{

	jump = true;
	uint32_t branch_delay = pc + 4;
	jump_addr = branch_delay & 0xF0000000;
	jump_addr += j_address << 2;
	registers[31] = pc + 8;
}





#ifndef INSTRUCT
#define	INSTRUCT

#include<iostream>
#include "memory.hpp"
#include "global_vars.hpp"

class instruction_class
{
private:
	uint32_t instr;
	uint8_t opcode;
	uint8_t r_source1;
	uint8_t r_source2;
	uint8_t r_dest;
	uint8_t r_shiftamt;
	uint8_t r_fn;
	uint8_t i_source1;
	uint8_t i_dest;
	uint16_t i_Astart;
	uint32_t j_address;
	char type;

	void extract_r();
	void extract_j();
	void extract_i();


	void execute_r(std::vector<int32_t>& registers, memory mips_mem);
	void execute_j(std::vector<int32_t>& registers, memory mips_mem);
	void execute_i(std::vector<int32_t>& registers, memory mips_mem);

	void addu(std::vector<int32_t>& registers);
	void add(std::vector<int32_t>& registers);
	void jr(std::vector<int32_t>& registers);
	void and_r(std::vector<int32_t>& registers);
	void or_r(std::vector<int32_t>& registers);
	void xor_r(std::vector<int32_t>& registers);
	void ssl(std::vector<int32_t>& registers);

	void addi(std::vector<int32_t>& registers);
	void lw(std::vector<int32_t>& registers, memory mips_mem);
	void sw(std::vector<int32_t>& registers, memory mips_mem);
	void lui(std::vector<int32_t>& registers);
	void ori(std::vector<int32_t>& registers);

public:
	instruction_class();
	instruction_class(uint32_t instr_in);
	void delayed_init(uint32_t instr_in);
	void decode();
	void execute(std::vector<int32_t>& registers, memory mips_mem);

};

#endif // !INSTRUCT


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


	void execute_r(std::vector<int32_t>& registers);
	void execute_j(std::vector<int32_t>& registers, memory mips_mem);
	void execute_i(std::vector<int32_t>& registers, memory& mips_mem);

	void addu(std::vector<int32_t>& registers);
	void add(std::vector<int32_t>& registers);
	void sub(std::vector<int32_t>& registers);
	void subu(std::vector<int32_t>& registers);
	void jr(std::vector<int32_t>& registers);
	void jalr(std::vector<int32_t>& registers);
	void and_r(std::vector<int32_t>& registers);
	void or_r(std::vector<int32_t>& registers);
	void xor_r(std::vector<int32_t>& registers);
	void div(std::vector<int32_t>& registers);
	void divu(std::vector<int32_t>& registers);
	void mult(std::vector<int32_t>& registers);
	void multu(std::vector<int32_t>& registers);
	void sll(std::vector<int32_t>& registers);
	void sllv(std::vector<int32_t>& registers);
	void srl(std::vector<int32_t>& registers);
	void srlv(std::vector<int32_t>& registers);
	void sra(std::vector<int32_t>& registers);
	void srav(std::vector<int32_t>& registers);
	void slt(std::vector<int32_t>& registers);
	void sltu(std::vector<int32_t>& registers);
	void mfhi(std::vector<int32_t>& registers);
	void mflo(std::vector<int32_t>& registers);
	void mthi(std::vector<int32_t>& registers);
	void mtlo(std::vector<int32_t>& registers);

	void addi(std::vector<int32_t>& registers);
	void addiu(std::vector<int32_t>& registers);
	void andi(std::vector<int32_t>& registers);
	void lw(std::vector<int32_t>& registers, memory& mips_mem);
	void sw(std::vector<int32_t>& registers, memory& mips_mem);
	void lui(std::vector<int32_t>& registers);
	void ori(std::vector<int32_t>& registers);
	void lb(std::vector<int32_t>& registers, memory& mips_mem);
	void lbu(std::vector<int32_t>& registers, memory mips_mem);
	void lh(std::vector<int32_t>& registers, memory mips_mem);
	void lhu(std::vector<int32_t>& registers, memory mips_mem);
	void lwl(std::vector<int32_t>& registers, memory mips_mem);
	void lwr(std::vector<int32_t>& registers, memory mips_mem);
	void sb(std::vector<int32_t>& registers, memory& mips_mem);
	void sh(std::vector<int32_t>& registers, memory& mips_mem);
	void slti(std::vector<int32_t>& registers);
	void sltiu(std::vector<int32_t>& registers);
	void xori(std::vector<int32_t>& registers);
	void beq(std::vector<int32_t>& registers);
	void bgez(std::vector<int32_t>& registers);
	void bgezal(std::vector<int32_t>& registers);
	void bgtz(std::vector<int32_t>& registers);
	void blez(std::vector<int32_t>& registers);
	void bltz(std::vector<int32_t>& registers);
	void bltzal(std::vector<int32_t>& registers);
	void bne(std::vector<int32_t>& registers);

	void j();
	void jal(std::vector<int32_t>& registers);


public:
	instruction_class();
	instruction_class(uint32_t instr_in);
	void delayed_init(uint32_t instr_in);
	void decode();
	void execute(std::vector<int32_t>& registers, memory& mips_mem);

};

#endif // !INSTRUCT


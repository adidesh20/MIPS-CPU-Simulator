#ifndef INSTRUCT
#define	INSTRUCT

#include<iostream>

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

	void look_up_r();
	void look_up_j();
	void look_up_i();
	void add(std::vector<uint32_t> registers);

public:
	instruction_class(uint32_t instr);
	void decode();
	void look_up(std::vector<uint32_t> registers);
	
};

#endif // !INSTRUCT


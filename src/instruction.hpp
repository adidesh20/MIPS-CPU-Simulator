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

public:
	instruction(uint32_t instr);
	void decode();
	void look_up();

};

#endif // !INSTRUCT


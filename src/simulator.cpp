#include <iostream>
#include<string>
#include <fstream>
#include <cstdlib>

#include "memory.hpp"
//#include "memory.cpp"

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

	memory mips(bin);


	
	


	

	 


	
	
	


}
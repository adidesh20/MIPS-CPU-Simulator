#include <iostream>
#include<string>
#include <fstream>
#include <cstdlib>

//#include "memory.hpp"
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

	std::ifstream bin(binName.c_str, std::ios::in | std::ios::binary | std::ios::ate);
	//bin.open(binFile.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	
	if (!bin.is_open())
	{
		std::cout << "Could not open binary" << std::endl;
		return(-21);
	}
	else
	{
		std::cerr << "File was found!";
		return 0;
	}

	 


	
	
	


}
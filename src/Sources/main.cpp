#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Includes/CPU.h"

CPU _CPU;
std::string target_path = "";


void print_memory(unsigned int start = 0, unsigned int end = 1048575)
{
	for (unsigned int idx = start; idx <= end; idx++)
	{
		std::printf("%5X : |", idx);
		for (unsigned int sub_idx = 0; sub_idx < 4; sub_idx++)
		{
			std::printf("%2X|", _CPU.Memory[idx]);
			idx++;
		}
		std::printf("\n");
	}
}

bool load_rom_data(std::string path,std::vector<unsigned char>& data)
{
	std::ifstream file(path, std::ifstream::binary);
	if (file) {
		file.seekg(0, file.end);
		int length = (int)file.tellg();
		file.seekg(0, file.beg);

		unsigned char * buffer = (unsigned char*)malloc(length);

		file.read((char*)buffer, length);
		file.close();
		data.resize(length);
		for(int i = 0; i < length; i++)
		{
			data[i] = buffer[i];
		}

		free(buffer);
		return true;
	}
	else
		return false;
}

int main(int argc,char** argv)
{
	std::cout << "TEST BUILD!\n";


	if(argc < 2)
		return 0;

	std::string path = argv[1];
	target_path = path;
	std::cout << "EXECUTE ROM=" << target_path << "\n";

	for(int i = 2; i < argc; i++)
	{
		std::string cmd = argv[i];
		if(cmd == "-m")
		{
			if(i + 1 >= argc)
				return 0;
			
			std::string mode = argv[i + 1];
			if(mode == "DEBUG")
			{
				_CPU.CPU_MODE = CPU::CPU_MODE::DEBUG_LOG;
				std::cout << "CPU RUN DEBUG MODE\n";
			}
			else if(mode == "REAL")
			{
				_CPU.CPU_MODE = CPU::CPU_MODE::REAL;
				std::cout << "CPU RUN REAL MODE\n";
			}
			else
				return 0;
		}
	}

	std::vector<unsigned char> rom;

	bool load_result = load_rom_data(target_path,rom);

	if(!load_result && rom.size() != _CPU.ROM_SIZE)
		return 0;

	_CPU.CPU_INIT(rom);
	//print_memory();

	clock_t s = clock();
	int cycle = 0;
	while (_CPU.Execute())
	{
		cycle++;
		std::cout << "CYCLE " << cycle << "\n";
		if(cycle == 30)
		{
			break;
		}
	}
	double dur = (double)(clock() - s);
	std::cout << "RUN TIME : " << (double)dur << " || " << cycle << " cycle\n";
	//print_memory(0x400, 0x501);

	return 0;
}
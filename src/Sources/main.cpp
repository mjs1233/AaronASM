#include <iostream>
#include <vector>
#include <string>
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

int main(int argc,char** argv)
{
	std::cout << "TEST BUILD!\n";


	if(argc < 2)
		return 0;

	for(int i = 1; i < argc; i++)
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
		if(cmd == "-t")
		{
			if(i + 1 >= argc)
				return 0;
			
			std::string path = argv[i + 1];
			target_path = path;
			std::cout << "EXECUTE ROM=" << target_path << "\n";
		}
	}

	//print_memory();
	INSTRUCTION_BLOCK inst;
	inst.OpType = 1;
	inst.OpCode = LDR;
	inst.RegisterSelect = 0;
	inst.Body = 0xFFFFF;
	SetMemory(0x400, inst.DATA, _CPU.Memory);

	inst.OpType = 1;
	inst.OpCode =  BRZ;
	inst.RegisterSelect = 0;
	inst.Body = 0x400+28;
	SetMemory(0x400 + 4, inst.DATA, _CPU.Memory);
	inst.OpType = 1;
	inst.OpCode = SUB;
	inst.RegisterSelect = 0;
	inst.Body = 1;
	SetMemory(0x400 + 8, inst.DATA, _CPU.Memory);
	inst.OpType = 1;
	inst.OpCode = BRC;
	inst.RegisterSelect = 0;
	inst.Body = 0x400;
	SetMemory(0x400 + 12, inst.DATA, _CPU.Memory);

	inst.OpType = 1;
	inst.OpCode = LDR;
	inst.RegisterSelect = 0;
	inst.Body = 0xF;
	SetMemory(0x400 + 32, inst.DATA, _CPU.Memory);
	inst.OpType = 1;
	inst.OpCode = STR;
	inst.RegisterSelect = 0;
	inst.Body = 0x500;
	SetMemory(0x400 + 36, inst.DATA, _CPU.Memory);
	inst.OpType = 2;
	inst.OpCode = HLT;
	inst.RegisterSelect = 0;
	inst.Body = 0;
	SetMemory(0x400 + 40, inst.DATA, _CPU.Memory);


	//print_memory(0x400, 0x501);
	clock_t s = clock();
	int cycle = 0;
	while (_CPU.Execute())
	{
		cycle++;
		//std::cout << "SP: " << _CPU.Register.PC << "\n";
	}
	double dur = (double)(clock() - s);
	std::cout << "RUN TIME : " << (double)dur << " || " << cycle << " cycle\n";
	//print_memory(0x400, 0x501);

	return 0;
}
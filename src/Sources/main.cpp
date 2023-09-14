#include <iostream>
#include <vector>
#include "CPU.h"

CPU _CPU;


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

int main(void)
{
	std::cout << "TEST BUILD!\n\n\n";

	_CPU.CPU_MODE = CPU::CPU_MODE::DEBUG_LOG;
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
	std::cout << "S\n";
	clock_t s = clock();
	int cycle = 0;
	while (_CPU.Execute())
	{
		cycle++;
		//std::cout << "SP: " << _CPU.Register.PC << "\n";
	}
	double dur = (double)(clock() - s);
	std::cout << "RUN TIME : " << (double)dur << " || " << cycle << " cycle";
	//print_memory(0x400, 0x501);

	return 0;
}
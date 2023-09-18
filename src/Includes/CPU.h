#pragma once
#include <vector>
#include <iostream>
#include "Register.h"
#include "InstructionBlock.h"
#include "Instruction.h"

//using INSTRUCTION_FUNCTION = bool(*)(INSTRUCTION_BLOCK instruction,Register& reg, std::vector<unsigned char>& memory);

class CPU
{
public:
	enum class CPU_MODE
	{
		REAL,
		DEBUG_LOG
	};
public:
	Register Register_;
	std::vector<unsigned char> Memory;
	std::vector<std::vector<INSTRUCTION_FUNCTION>> Instructions;

	const int MEMORY_SIZE = 0xFFFFF;
	const int RAM_SIZE = 0x7FFFF;
	const int ROM_OFFSET = 0x80000;
	const int ROM_SIZE = 0x7FFFF;
	CPU_MODE CPU_MODE = CPU_MODE::DEBUG_LOG;
	unsigned int PREV_PC = 0x400;

	CPU()
	{
		Memory.resize(MEMORY_SIZE);
		Instructions.resize(64, std::vector<INSTRUCTION_FUNCTION>(4));
		Register_.PC = 0x400;
		Register_.SP = 0x10;

		Instructions[LDR][0] = LDR_M;
		Instructions[LDR][1] = LDR_I;

		Instructions[STR][1] = STR_I;

		Instructions[ADD][0] = ADD_M;
		Instructions[ADD][1] = ADD_I;

		Instructions[SUB][0] = SUB_M;
		Instructions[SUB][1] = SUB_I;

		Instructions[MUL][0] = MUL_M;
		Instructions[MUL][1] = MUL_I;

		Instructions[DIV][0] = DIV_M;
		Instructions[DIV][1] = DIV_I;
		
		Instructions[RMD][0] = RMD_M;
		Instructions[RMD][1] = RMD_I;
	
		Instructions[SFL][0] = SFL_M;
		Instructions[SFL][1] = SFL_I;
		
		Instructions[SFR][0] = SFR_M;
		Instructions[SFR][1] = SFR_I;

		Instructions[OR][0] = OR_M;
		Instructions[OR][1] = OR_I;

		Instructions[AND][0] = AND_M;
		Instructions[AND][1] = AND_I;

		Instructions[XOR][0] = XOR_M;
		Instructions[XOR][1] = XOR_I;

		Instructions[NOT][2] = NOT_;

	
		Instructions[JMP][0] = JMP_M;
		Instructions[JMP][1] = JMP_I;
		
		Instructions[JPZ][0] = JPZ_M;
		Instructions[JPZ][1] = JPZ_I;
		
		Instructions[JPN][0] = JPN_M;
		Instructions[JPN][1] = JPN_I;

		Instructions[RET][2] = RET_;

		Instructions[BRH][0] = BRH_M;
		Instructions[BRH][1] = BRH_I;

		Instructions[BRZ][0] = BRZ_M;
		Instructions[BRZ][1] = BRZ_I;


		Instructions[NOP][2] = NOP_;

		Instructions[HLT][2] = HLT_;

		Instructions[HLT][2] = CLS_;

	}

	bool CPU_INIT(std::vector<unsigned char>& rom_data)
	{
		for(int i = 0; i < ROM_SIZE; i++)
		{
			Memory[ROM_OFFSET + i] = rom_data[i];
		}
		//reset register
		Register_.A = 0;
		Register_.X = 0;
		Register_.Y = 0;
		Register_.SP = 0;
	}

	bool Execute()
	{
		INSTRUCTION_BLOCK instruction;
		instruction.DATA = GetMemory(Register_.PC, Memory);
		bool error_flag = Instructions[instruction.OpCode][instruction.OpType](instruction, Register_, Memory);
		if (!error_flag && CPU_MODE == CPU_MODE::DEBUG_LOG)
		{
			if (instruction.OpCode == HLT)
			{
				return false;
			}
			std::cout << "VM ERROR! error_flag enabled\nCUR PC: " + Register_.PC << " PREV PC: " + PREV_PC << "\n";
		}
		PREV_PC = Register_.PC;
		Register_.PC += 4;
		return true;
	}

};


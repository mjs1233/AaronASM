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
	Register Register;
	std::vector<unsigned char> Memory;
	std::vector<std::vector<INSTRUCTION_FUNCTION>> Instructions;

	const int MEMORY_SIZE = 1048575;
	CPU_MODE CPU_MODE = CPU_MODE::DEBUG_LOG;
	unsigned int PREV_PC = 0x400;

	CPU()
	{
		Memory.resize(MEMORY_SIZE);
		Instructions.resize(64, std::vector<INSTRUCTION_FUNCTION>(4));
		Register.PC = 0x400;
		Register.SP = 0x10;

		Instructions[LDR][0] = LDR_M;
		Instructions[LDR][1] = LDR_I;

		Instructions[STR][1] = STR_I;

		Instructions[ADD][0] = ADD_M;
		Instructions[ADD][1] = ADD_I;

		Instructions[SUB][0] = SUB_M;
		Instructions[SUB][1] = SUB_I;

		Instructions[JMP][0] = JMP_M;
		Instructions[JMP][1] = JMP_I;

		Instructions[JPZ][0] = JPZ_M;
		Instructions[JPZ][1] = JPZ_I;

		Instructions[BRC][0] = BRC_M;
		Instructions[BRC][1] = BRC_I;

		Instructions[BRZ][0] = BRZ_M;
		Instructions[BRZ][1] = BRZ_I;

		Instructions[RET][2] = RET_;

		Instructions[HLT][2] = HLT_;

	}

	bool Execute()
	{
		INSTRUCTION_BLOCK instruction;
		instruction.DATA = GetMemory(Register.PC, Memory);
		bool error_flag = Instructions[instruction.OpCode][instruction.OpType](instruction, Register, Memory);
		if (!error_flag && CPU_MODE == CPU_MODE::DEBUG_LOG)
		{
			std::cout << "VM ERROR! error_flag enabled\nCUR PC: " + Register.PC << " PREV PC: " + PREV_PC << "\n";
			if (instruction.OpCode == HLT)
			{
				return false;
			}
			std::cout << "VM ERROR! error_flag enabled\nCUR PC: " + Register.PC << " PREV PC: " + PREV_PC << "\n";
		}
		PREV_PC = Register.PC;
		Register.PC += 4;
		return true;
	}

};


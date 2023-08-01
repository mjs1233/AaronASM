#include "Instruction.h"


inline unsigned int GetMemory(unsigned int pointer, std::vector<unsigned char>& memory)
{
	unsigned int offset_0 = (unsigned int)memory[pointer];
	unsigned int offset_1 = (unsigned int)memory[pointer + 1] << 8;
	unsigned int offset_2 = (unsigned int)memory[pointer + 2] << 16;
	unsigned int offset_3 = (unsigned int)memory[pointer + 3] << 24;
	return offset_0 + offset_1 + offset_2 + offset_3;
}

inline void SetMemory(unsigned int pointer, unsigned int value, std::vector<unsigned char>& memory)
{
	memory[pointer] = (unsigned char)value;
	memory[pointer + 1] = (unsigned char)(value >> 8);
	memory[pointer + 2] = (unsigned char)(value >> 16);
	memory[pointer + 3] = (unsigned char)(value >> 24);
}


bool LDR_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int target_addr = instruction.Body;
	SetRegister(reg, instruction.RegisterSelect, GetMemory(target_addr, memory));
	return true;
}


bool LDR_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	SetRegister(reg, instruction.RegisterSelect, instruction.Body);
	return true;
}

bool STR_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int target_addr = instruction.Body;
	SetMemory(target_addr, GetRegister(reg, instruction.RegisterSelect), memory);
	return true;
}


bool ADD_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int target_addr = instruction.Body;
	unsigned int prev_reg = GetRegister(reg, instruction.RegisterSelect);
	unsigned int updated_reg = prev_reg + GetMemory(target_addr, memory);

	reg.OV = prev_reg > updated_reg;
	reg.ZR = updated_reg == 0;
	reg.NG = updated_reg & 0b10000000000000000000000000000000;

	SetRegister(reg, instruction.RegisterSelect, updated_reg);

	return true;
}


bool ADD_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int prev_reg = GetRegister(reg, instruction.RegisterSelect);
	unsigned int updated_reg = prev_reg + instruction.Body;

	reg.OV = prev_reg > updated_reg;
	reg.ZR = updated_reg == 0;
	reg.NG = updated_reg & 0b10000000000000000000000000000000;

	SetRegister(reg, instruction.RegisterSelect, updated_reg);

	return true;
}


bool SUB_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int target_addr = instruction.Body;
	unsigned int prev_reg = GetRegister(reg, instruction.RegisterSelect);
	unsigned int updated_reg = prev_reg - GetMemory(target_addr, memory);

	reg.OV = prev_reg < updated_reg;
	reg.ZR = updated_reg == 0;
	reg.NG = updated_reg & 0b10000000000000000000000000000000;

	SetRegister(reg, instruction.RegisterSelect, updated_reg);

	return true;
}


bool SUB_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int prev_reg = GetRegister(reg, instruction.RegisterSelect);
	unsigned int updated_reg = prev_reg - instruction.Body;

	reg.OV = prev_reg < updated_reg;
	reg.ZR = updated_reg == 0;
	reg.NG = updated_reg & 0b10000000000000000000000000000000;

	SetRegister(reg, instruction.RegisterSelect, updated_reg);

	return true;
}

bool JMP_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (reg.SP == 252)
		return false;

	unsigned int target_addr = instruction.Body;
	unsigned int sub_pc = GetMemory(target_addr, memory);
	SetMemory(reg.SP, reg.PC, memory);
	reg.SP += 4;
	reg.PC = sub_pc;
	return true;
}


bool JMP_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (reg.SP == 252)
		return false;

	unsigned int sub_pc = instruction.Body;
	SetMemory(reg.SP, reg.PC, memory);
	reg.SP += 4;
	reg.PC = sub_pc;
	return true;
}


bool JPZ_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (!reg.ZR)
		return true;

	if (reg.SP == 252)
		return false;

	unsigned int target_addr = instruction.Body;
	unsigned int sub_pc = GetMemory(target_addr, memory);
	SetMemory(reg.SP, reg.PC, memory);
	reg.SP += 4;
	reg.PC = sub_pc;
	return true;
}


bool JPZ_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (!reg.ZR)
		return true;

	if (reg.SP == 252)
		return false;

	unsigned int sub_pc = instruction.Body;
	SetMemory(reg.SP, reg.PC, memory);
	reg.SP += 4;
	reg.PC = sub_pc;
	return true;
}


bool RET_(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (reg.SP == 16)
		return false;

	reg.SP -= 4;
	unsigned int prev_pc = GetMemory(reg.SP, memory);
	SetMemory(reg.SP, 0, memory);
	reg.PC = prev_pc;
	return true;
}


bool BRC_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int target_addr = instruction.Body;
	unsigned int brc_pc = GetMemory(target_addr, memory);
	reg.PC = brc_pc;
	return true;
}


bool BRC_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	unsigned int brc_pc = instruction.Body;
	reg.PC = brc_pc;
	return true;
}


bool BRZ_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (!reg.ZR)
		return true;
	unsigned int target_addr = instruction.Body;
	unsigned int brc_pc = GetMemory(target_addr, memory);
	reg.PC = brc_pc;
	return true;
}


bool BRZ_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	if (!reg.ZR)
		return true;
	unsigned int brc_pc = instruction.Body;
	reg.PC = brc_pc;
	return true;
}


bool HLT_(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory)
{
	return false;
}
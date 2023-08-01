#pragma once
/*
REGISTER
A  32
X  32
Y  32
PC 16
SP 16
 
OP TYPE
TYPE M : [OP TYPE[2]][OPCODE[6]][REGISTER SELECT[4]][MEMORY ADDRESS[20]]
TRG = MEMORY[MEMORY ADDRESS]
TYPE I : [OP TYPE[2]][OPCODE[6]][REGISTER SELECT[4]][IMMEDIATE VALUE[20]]
TRG = REGISTER(REGISTER SELECT)
TYPE A : [OP TYPE[2]][OPCODE[6]][REGISTER SELECT[4]]
TRG = MEMORY[REGISTER(REGISTER SELECT)]

A)Register
0. LDR : load register
1. STR : store register into memory (I)
B)Arithmetic
5. ADD : REG(A) = REG + TRG (OVF,ZR,NG,CR)
6. SUB : REG(A) = REG - TRG (OVF,ZR,NG,CR)
7. MUL : REG(A) = REG * TRG (OVF,ZR,NG)
8. DIV : REG(A) = REG / TRG (OVF,ZR,NG)
C)Logical
10. SFL : REG(A) = REG << TRG (OVF,ZR,NG)
11. SFR : REG(A) = REG >> TRG (OVF,ZR,NG)
12. OR  : REG(A) = REG | TRG (ZR,NG)
13. AND : REG(A) = REG & TRG (ZR,NG)
14. XOR : REG(A) = REG ^ TRG (ZR,NG)
15. NOT : REG(A) = !TRG (ZR,NG)
D)Flow
20. JMP : REG(PC) = TRG unconditional jump (SP)
21. JPZ : REG(PC) = TRG jump if zero (SP)
22. JPN : REG(PC) = TRG jump if negative (SP)
23. JPO : REG(PC) = TRG jump if overflow (SP)
24. JPC : REG(PC) = TRG jump if carry (SP)
25. RET 
26. BRC : REG(PC) = TRG unconditional branch
27. BRZ : REG(PC) = TRG branch if zero
E)Other
60. NOP : no operation
61. HLT : halt
*/
//
#define LDR 0
#define STR 1
#define ADD 5
#define SUB 6
#define MUL 7
#define DIV 8

#define SFL 10
#define SFR 11
#define OR 12
#define AND 13
#define XOR 14
#define NOT 15

#define JMP 20
#define JPZ 21
#define JPN 22
#define JPO 23
#define JPC 24
#define RET 25
#define BRC 26
#define BRZ 27

#define NOP 60
#define HLT 61


#include <vector>
#include "Register.h"
#include "InstructionBlock.h"

using INSTRUCTION_FUNCTION = bool(*)(INSTRUCTION_BLOCK instruction,Register& reg, std::vector<unsigned char>& memory);

inline unsigned int GetMemory(unsigned int pointer, std::vector<unsigned char>& memory);
inline void SetMemory(unsigned int pointer, unsigned int value, std::vector<unsigned char>& memory);


bool LDR_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool LDR_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool STR_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);


bool ADD_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool ADD_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool SUB_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool SUB_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);


bool JMP_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool JMP_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool JPZ_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool JPZ_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool RET_(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool BRC_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool BRC_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool BRZ_M(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
bool BRZ_I(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);

bool HLT_(INSTRUCTION_BLOCK instruction, Register& reg, std::vector<unsigned char>& memory);
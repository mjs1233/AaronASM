#pragma once

struct Register
{
	unsigned int A = 0;
	unsigned int X = 0;
	unsigned int Y = 0;
	unsigned int I = 0;//interrupt jump target
	unsigned int PC = 0;
	unsigned char SP = 0;
	unsigned char ZR : 1;
	unsigned char NG : 1;
	unsigned char OV : 1;
	unsigned char CR : 1;
	unsigned char INT : 1;//interrupt
};

void SetRegister(Register& reg, unsigned char register_select, unsigned int value);
unsigned int GetRegister(Register& reg, unsigned char register_select);
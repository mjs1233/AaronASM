#include "Register.h"

void SetRegister(Register& reg,unsigned char register_select,unsigned int value)
{
	switch (register_select)
	{
	case 0b00:
		reg.A = value;
		break;

	case 0b01:
		reg.X = value;
		break;

	case 0b10:
		reg.Y = value;
		break;
	};
}


unsigned int GetRegister(Register& reg, unsigned char register_select)
{
	switch (register_select)
	{
	case 0b00:
		return reg.A;
		break;

	case 0b01:
		return reg.X ;
		break;

	case 0b10:
		return reg.Y;
		break;
	};
}
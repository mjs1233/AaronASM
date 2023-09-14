#pragma once

union INSTRUCTION_BLOCK
{
	struct
	{
		unsigned int OpType : 2;
		unsigned int OpCode : 6;
		unsigned int RegisterSelect : 4;
		unsigned int Body : 20;
	};

	unsigned int DATA;
};


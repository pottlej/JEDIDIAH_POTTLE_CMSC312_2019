/*
 * cpu.cpp
 */
#include <iostream>
#include <cmath>
using namespace std;

class Cpu
{
	private:
		// Establishes operation codes that can be used.
		enum
		{
			OP_CALC,
			OP_IO,
			OP_YIELD,
			OP_OUT
		};

	public:
		// Establishes registers.
		enum
		{
			R0,
			R1,
			R2,
			R3,
			R4,
			R5,
			R6,
			R7,
			RPC,
			RCOUNT
		};

		uint16_t registers[RCOUNT];


	public:
		Cpu()
		{

		}

	private:
		void calc()
		{

		}

		void io()
		{
			//rand() % 25 + 25;
		}

		void yield()
		{

		}

		void out()
		{

		}

	public:
		int getRegisters()
		{
			return RCOUNT;
		}
		//Control Unit: extracts instructions from memory
		//and decodes and executes them

};


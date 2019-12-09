/*
 * memory.cpp
 */
#include <iostream>
#include <cmath>
#include "memory.h"
using namespace std;

//Public members
Memory::Memory(){}

Memory::Memory(uint64_t size)
{
	setMemory(size);
}

Memory::~Memory()
{
	free(memory);
	memorySet = 0;
}

// Writes an instruction to an address location.
void Memory::write(uint64_t address, uint64_t instruction)
{
	memory[address] = instruction;
}

// Returns an instruction from an address location.
uint64_t Memory::read(uint64_t address)
{
	return memory[address];
}



// Private members
void Memory::setMemory(uint64_t size)
{
	uint64_t numAddresses = size / sizeof(uint64_t);

	memory = (uint64_t*) malloc(numAddresses);
	memorySet = 1;

	// Tests memory for allocation.
	if (memory == 0)
	{
		free(memory);
		memorySet = 0;
	}
}




/*
 * memory.cpp
 *
 * Jedidiah Pottle
 * CMSC312
 */
#include <iostream>
#include <cmath>
#include "memory.h"
using namespace std;

Memory::Memory(uint64_t size)
{
	setMemory(size);
}

Memory::~Memory()
{
	free(memory);
	memorySet = false;
}

uint64_t Memory::getCapacity()
{
	return capacity;
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

void Memory::setMemory(uint64_t size)
{
	uint64_t numAddresses = size / sizeof(uint64_t);
	capacity = numAddresses;

	memory = (uint64_t*) malloc(numAddresses);
	memorySet = true;

	// Tests memory for allocation.
	if (memory == 0)
	{
		free(memory);
		memorySet = false;
	}
}




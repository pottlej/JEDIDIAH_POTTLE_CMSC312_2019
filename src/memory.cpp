/*
 * memory.cpp
 */
#include <iostream>
#include <cmath>
#include "memory.h"
using namespace std;

//Public members
// Default constructor
Memory::Memory(){}

// Parameter constructor
Memory::Memory(uint64_t size)
{
	setMemory(size);
}

// Deconstructor
Memory::~Memory()
{
	free(memory);
}

uint64_t Memory::getAddressSpace()
{
	return space;
}

void Memory::write(uint64_t address, uint64_t instruction)
{
	memory[address] = instruction;
}

uint64_t Memory::read(uint64_t address)
{
	return memory[address];
}

// Private members
void Memory::setMemory(uint64_t size)
{
	cout << "size: " << size << endl;

	/*
	// Calculates number of memory locations needed.
	int exp = ceil(log2(size/2));
	unsigned long int numAddresses = pow(2, exp);
	cout << "addresses: " << numAddresses << endl;
	*/

	uint64_t numAddresses = size / sizeof(uint64_t);
	space = numAddresses;
	//cout << "addresses: " << numAddresses << endl;

	memory = (uint64_t*) malloc(numAddresses);

	// Makes sure memory is eventually allocated.
	if (memory == NULL)
	{
		cout << "memory not set" << endl;
		free(memory);
		setMemory(size);
	}
	cout << "memory set" << endl;
}




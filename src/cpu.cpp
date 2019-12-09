/*
 * cpu.cpp
 * Central Processing Unit
 */
#include <algorithm>
#include <cmath>
#include "cpu.h"
using namespace std;

// Public Members
Cpu::Cpu(size_t cacheSize, Memory *memoryMain)
{
	setCacheSize(cacheSize);
	setMemoryMain(memoryMain);
	initRegisters();
}

Cpu::~Cpu()
{
	free(registers);
}

void Cpu::writeCache(uint64_t tag, uint64_t instruction)
{
	cache[tag] = instruction;
}

uint64_t Cpu::readCache(uint64_t tag)
{
	unordered_map<uint64_t, uint64_t>::const_iterator found = cache.find(tag);
	if (found == cache.end())
	{
		return numeric_limits<uint64_t>::max();
	}
	return found->second;
}

void Cpu::writeMemory(uint64_t address, uint64_t instruction)
{
	memoryMain->write(address, instruction);
}

uint64_t Cpu::readMemory(uint64_t address)
{
	return memoryMain->read(address);
}


//Private Members
void Cpu::setCacheSize(size_t size)
{
	this->cacheSize = size;
}

void Cpu::setMemoryMain(Memory *memoryMain)
{
	this->memoryMain = memoryMain;
}

void Cpu::initRegisters()
{
	registers = (unsigned int*) calloc(R_COUNT, sizeof(unsigned int));
}

void Cpu::calc()
{

}

void Cpu::io()
{
	//rand() % 25 + 25;
}

void Cpu::yield()
{

}

void Cpu::out()
{

}


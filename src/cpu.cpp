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

void Cpu::writeCache(unsigned int tag, unsigned int data)
{
	cache[tag] = data;
}

unsigned int Cpu::readCache(unsigned int tag)
{
	unordered_map<unsigned int, unsigned int>::const_iterator found = cache.find(tag);
	if (found == cache.end())
	{
		return numeric_limits<unsigned int>::max();
	}
	return found->second;
}

void Cpu::writeMemory(unsigned int address, unsigned int instruction)
{
	memoryMain->write(address, instruction);
}

unsigned int Cpu::readMemory(unsigned int address)
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


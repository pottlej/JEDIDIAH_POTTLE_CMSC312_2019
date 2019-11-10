/*
 * mmu.cpp
 * Memory Management Unit
 */
#include <cmath>
#include <iostream>
#include "mmu.h"
using namespace std;

// Public members
//Constructor
Mmu::Mmu(uint64_t physicalSpace, uint64_t virtualSpace, uint64_t blockSize)
{
	setNumFrames(physicalSpace, blockSize);
	setNumPages(virtualSpace, blockSize);
}

uint64_t Mmu::getNumFrames()
{
	return numFrames;
}

uint64_t Mmu::getNumPages()
{
	return numPages;
}



//Private members
void Mmu::setNumFrames(uint64_t physicalSpace, uint64_t size)
{
	numFrames = physicalSpace / size;
}

void Mmu::setNumPages(uint64_t logicalSpace, uint64_t size)
{
	numPages = logicalSpace / size;
}


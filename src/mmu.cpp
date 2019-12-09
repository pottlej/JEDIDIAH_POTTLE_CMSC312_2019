/*
 * mmu.cpp
 * Memory Management Unit
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include "mmu.h"
using namespace std;

// Public members
Mmu::Mmu(uint64_t blockSize, uint64_t physicalSpace, uint64_t logicalSpace)
{
	setNumFrames(physicalSpace, blockSize);
	setNumPages(logicalSpace, blockSize);
	initPageTable(numPages);
}

uint64_t Mmu::getNumFrames()
{
	return numFrames;
}

uint64_t Mmu::getNumPages()
{
	return numPages;
}

void Mmu::addPageData(uint64_t pageNum, uint64_t baseAddress)
{
	_page *page = pageTable;

	while (page->pageNum != pageNum)
	{
		page = page->next;
	}

	page->baseAddress = baseAddress;

	removeFreeFrame(pageNum);
}

void Mmu::removePageData(uint64_t pageNum)
{
	_page *page = pageTable;

	while (page->pageNum != pageNum)
	{
		page = page->next;
	}

	page->isVal = 0;
	page->isRef = 0;
	page->isMod = 0;
	page->baseAddress = 0;

	addFreeFrame(pageNum);
}



//Private members
void Mmu::setNumFrames(uint64_t physicalSpace, uint64_t blockSize)
{
	numFrames = physicalSpace / blockSize;
}

void Mmu::setNumPages(uint64_t logicalSpace, uint64_t blockSize)
{
	numPages = logicalSpace / blockSize;
}

void Mmu::initPageTable(uint64_t size)
{
	uint64_t count = 1;
	pageTable = new _page;
	_page *current = pageTable;

	while (count < size)
	{
		_page *newPage = new _page;
		newPage->pageNum = count;

		current->next = newPage; // Sets next page.
		current = current->next; // Goes to next page.
		++count;
	}
}

void Mmu::addFreeFrame(uint64_t pageNum)
{
	freeFrames.insert(pageNum);
}

void Mmu::removeFreeFrame(uint64_t pageNum)
{
	set<uint64_t, less<uint64_t>>::iterator found = find(freeFrames.begin(), freeFrames.end(), pageNum);
	if (found != freeFrames.end())
	{
		freeFrames.erase(found);
	}
}


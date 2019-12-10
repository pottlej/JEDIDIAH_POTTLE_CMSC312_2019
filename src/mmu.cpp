/*
 * mmu.cpp
 * Memory Management Unit
 *
 * Jedidiah Pottle
 * CMSC312
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include "mmu.h"
using namespace std;

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

void Mmu::addPageData(uint64_t pageNum)
{
	_page *page = pageTable;

	while (page->pageNum != pageNum)
	{
		page = page->next;
	}

	page->baseAddress = getFreeFrame();
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

	addFreeFrame(page->baseAddress);
	page->baseAddress = 0;
}

void Mmu::setNumFrames(uint64_t physicalSpace, uint64_t blockSize)
{
	numFrames = physicalSpace / blockSize;

	for (uint64_t i = 0; i < numFrames; i++)
	{
		addFreeFrame(i);
	}
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

void Mmu::addFreeFrame(uint64_t frameNum)
{
	freeFrames.insert(frameNum);
}

uint64_t Mmu::getFreeFrame()
{
	set<uint64_t, less<uint64_t>>::iterator element = freeFrames.begin();
	freeFrames.erase(*element);

	return *element;
}


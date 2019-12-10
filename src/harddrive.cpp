/*
 * harddrive.cpp
 */

#include <iostream>
#include <sys/stat.h>
#include "harddrive.h"
using namespace std;

HardDrive::HardDrive(fstream &disk, uint64_t size, uint64_t blockSize) : harddrive(disk)
{
	capacity = size / sizeof(uint64_t);
	setNumBlocks(blockSize);

	if (fileExists(filename))
	{
		resumeHarddrive();
	}
	else
	{
		initHarddrive();
	}
}

uint64_t HardDrive::getAddress(uint64_t address)
{
	return 0;
}

uint64_t HardDrive::getCapacity()
{
	return capacity;
}

string HardDrive::getFilename()
{
	return filename;
}

bool HardDrive::write(uint64_t base, int offset, uint64_t instruction)
{
	uint64_t address = base + offset;

	bool success = false;
	if (address < capacity and instruction <= UINT64_MAX)
	{
		harddrive.open(filename);
		if (harddrive)
		{
			uint64_t line = address * 22;
			harddrive.seekp(line);
			harddrive << "00000000000000000000" << endl; // Resets address.

			uint64_t loc = getLoc(address, instruction);
			harddrive.seekp(loc);
			harddrive << instruction << endl;
			success = true;
		}
		harddrive.close();
	}

	return success;
}

uint64_t HardDrive::read(uint64_t address)
{
	uint64_t instruction = -1;
	if (address < capacity)
	{
		harddrive.open(filename, ios::in);
		if (harddrive)
		{
			uint64_t line = address * 22;
			string temp = "";
			getline(harddrive.seekg(line), temp);
			instruction = stoull(temp);
		}
	}
	harddrive.close();

	return instruction;
}

uint64_t HardDrive::getFreeBlock()
{
	set<uint64_t, less<uint64_t>>::iterator element = freeBlocks.begin();
	freeBlocks.erase(*element);

	return *element;
}

void HardDrive::setNumBlocks(uint64_t blockSize)
{
	numBlocks = capacity / blockSize;

	for (uint64_t i = 0; i < numBlocks; i++)
	{
		addFreeBlock(i);
	}
}

uint64_t HardDrive::getLoc(uint64_t address, uint64_t instruction)
{
	// Created by Kerrek SB (https://stackoverflow.com).
	uint64_t numDigits = 0;
	uint64_t num = instruction;
	do {
		 ++numDigits;
		 num /= 10;
	} while (num);

	uint64_t offset = address * 22; // Takes into account newlines.
	uint64_t loc = 20 - numDigits + offset; // Takes into account instruction length.

	return loc;
}

// Method created by Rico (https://stackoverflow.com).
bool HardDrive::fileExists(const std::string &filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

void HardDrive::addFreeBlock(uint64_t blockNum)
{
	freeBlocks.insert(blockNum);
}

void HardDrive::initHarddrive()
{
	harddrive.open(filename, ios::out);
	if (harddrive)
	{
		diskSet = true;

		string instruction = "00000000000000000000";
		for (uint64_t i = 0; i < capacity; i++)
		{
			harddrive << instruction << endl;
		}
	}

	harddrive.close();
}

// Associates harddrive with the file.
void HardDrive::resumeHarddrive()
{
	harddrive.open(filename);
	harddrive.close();
	diskSet = true;
}

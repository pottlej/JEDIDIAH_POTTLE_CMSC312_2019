/*
 * main.cpp
 *
 * Jedidiah Pottle
 * CMSC312
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "cpu.h"
#include "harddrive.h"
#include "memory.h"
#include "mmu.h"
#include "pcb.h"
#include "schedulerlong.h"
using namespace std;

#define SIZE_MEMORY_MAIN 4096 // Represents size of main memory.
#define SIZE_MEMORY_VIRTUAL 6144 // Represents size of virtual memory.
#define SIZE_BACKING_STORE 8192 // Represents size of backing store.
#define SIZE_CACHE_CPU 1024 // Represents size of CPU cache.
#define SIZE_BLOCK 4 // Represents size of paging block.

// Establishes operation codes that can be used.
enum
{
	CALC = 0,
	IO,
	YIELD,
	OUT,
	SECTION
};

// Delimits a string by a desired string and returns the desired value.
string getValue(string str, bool second, string delim)
{
	size_t pos = 0;
	string token;

	if (second)
	{
		while ((pos = str.find(delim)) != string::npos)
		{
			str.erase(0, pos + delim.length());
		}
	}
	else
	{
		while ((pos = str.find(delim)) != string::npos)
		{
			str.erase(pos, string::npos);
		}
	}

	token = str;

	return token;
}

// Gets the number of addresses pertaining to the memory size.
uint64_t getAddressSpace(uint64_t memorySize)
{
	uint64_t space = memorySize / sizeof(uint64_t);
	return space;
}

//Reads info from a "program" file.
vector<string> readProgram(string filename)
{
	vector<string> text; // Contains parsed program.
	ifstream program;
	program.open(filename);

	while(!program.eof())
	{
		string line = "";
		getline(program, line);
		if (line == "EXE")
		{
			break;
		}
		else if (!line.empty())
		{
			text.push_back(line);
		}
	}
	program.close();
	text.shrink_to_fit();

	return text;
}

// Creates an unique ID used by a PCB.
unsigned int createId(unordered_set<unsigned int> *pids)
{
	unsigned int max = numeric_limits<unsigned int>::max();

	unsigned int id = 0;
	while (id == 0)
	{
		unsigned int val = (rand() % (max - 1)) + 1;

		unordered_set<unsigned int>::const_iterator found = pids->find(val);
		if (found == pids->end())
		{
			id = val;
			pids->insert(id);
			break;
		}
	}

	return id;
}

//
Pcb createPCB(string filename, size_t numRegisters, unordered_set<unsigned int> *pids)
{
	// Initializes a Process Control Block using a "program" (.txt) file.
	unsigned int id = createId(pids);
	vector<string> program = readProgram(filename);
	string delim = ":";
	bool second = true;
	string name = getValue(program.at(0), second, delim);
	size_t burst = stoi(getValue(program.at(1), second, delim));
	uint64_t memory = stoi(getValue(program.at(2), second, delim));
	program.erase(program.begin(), program.begin() + 3);
	program.shrink_to_fit();

	return Pcb(id, name, burst, memory, program, numRegisters);
}

// Loads initial programs into hard drive.
void bootstrap(HardDrive harddrive)
{
	/*
	uint64_t block;
	uint64_t base = 0;
	uint64_t offset = 0;
	vector<string> program;

	// Loads Output Processes function into hard drive.
	block = harddrive.getFreeBlock();
	base = block * SIZE_BLOCK;
	harddrive.write(base, SECTION);
	++address;
	harddrive.write(address, OUT);
	++address;
	harddrive.write(address, SECTION);
	++address;
	*/
}

//
void close(int error)
{
	switch(error)
	{
		case 0:
			cout << "Good bye :)" << endl;
			break;

		case 1:
			cout << "Error allocating memory" << endl;
			break;

		case 2:
			cout << "Error creating hard drive space" << endl;
			break;

		default:
			cout << "Unknown error occurred!" << endl;
	}
	cout << "Shutting down..." << endl;
	exit(0);
}

//
int main()
{
	// Main Memory
	Memory memoryMain = Memory(SIZE_MEMORY_MAIN); // @suppress("Ambiguous problem")
	// Tests memory for allocation.
	if (!memoryMain.memorySet)
	{
		close(1);
	}
	Memory *ptrMain = &memoryMain; // Points to memoryMain.
	uint64_t spaceMain = memoryMain.getCapacity();

	// Backing Store (Hard Disk Drive)
	fstream harddrive;
	HardDrive hdd = HardDrive(harddrive, SIZE_BACKING_STORE, SIZE_BLOCK);
	// Tests hard drive for creation.
	if (!hdd.diskSet)
	{
		close(2);
	}

	//bootstrap(hdd); // Writes built-in functions to hard drive.

	// Virtual Memory
	uint64_t spaceVirtual = getAddressSpace(SIZE_MEMORY_VIRTUAL);

	// Memory Management Unit
	Mmu mmu = Mmu(SIZE_BLOCK, spaceMain, spaceVirtual);

	// Central Processing Unit
	Cpu cpu = Cpu(SIZE_CACHE_CPU, ptrMain);
	int rCount = cpu.R_COUNT; // Holds number of registers.

	// Process Queues
	vector<Pcb> qJob;
	vector<Pcb> qReady;
	vector<Pcb> qDeviceIO;

	unordered_set<unsigned int> pids; // Holds set of all current Process IDs being used.
	unordered_set<unsigned int> *ptrPids = &pids;
	/*
	for (const unsigned int& x: pids)
	{
		cout << ", " << x;
	}
	cout << endl;
	*/

	SchedulerLong jobScheduler = SchedulerLong(ptrMain);
	string filename = "user_programs\\Text Processor.txt";
	Pcb pcb = createPCB(filename, rCount, ptrPids);
	qJob.push_back(pcb);

	return 0;
};

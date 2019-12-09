/*
 * main.cpp
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
//#include <limits.h> // UINT_MAX
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "cpu.h"
#include "linkedlist.h"
#include "memory.h"
#include "mmu.h"
#include "pcb.h"
#include "schedulerlong.h"
using namespace std;

/*
string removeWhiteSpace(string str)
{
	//string output = str;
	//cout << output;
	//char whitespace[6] = {' ', '\t', '\n', '\v', '\f', '\r'};
	//int size = *(&whitespace + 1) - whitespace;
	string::iterator end = remove(str.begin(), str.end(), ' '); // Locates end of whitespace.
	str.erase(end, str.end());
	return str;
}
*/

/*
string stripWhiteSpace(string str)
{
	size_t i = 0; // Holds beginning of string without leading whitespace.
	size_t j = str.length() - 1; // Holds ending of string without trailing whitespace.
	if (str.compare("") != 0)
	{
		// Iterates from start of string.
		for (i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
			{
				break;
			}
		}

		if (i >= j)
		{
			return "";
		}

		// Iterates from end of string.
		for (j = str.length() - 1; j >= 0; j--)
		{
			if (str[j] != ' ')
			{
				break;
			}
		}
	}
	else
	{
		return "";
	}

	return str.substr(i, (j - i) + 1);
}
*/

string delimitValue(string str, string delim)
{
	size_t pos = 0;
	string token;
	while ((pos = str.find(delim)) != string::npos)
	{
	    str.erase(0, pos + delim.length());
	}

	//token = stripWhiteSpace(str);
	token = str;

	return token;
}

/*
vector<string> delimit(string str, string delim)
{
	size_t pos = 0;
	vector<string> tokens;
	while ((pos = str.find(delim)) != string::npos)
	{
		string token = str.substr(0, pos);
		token = stripWhiteSpace(token);
	    tokens.push_back(token);
	    str.erase(0, pos + delim.length());
	}
	str = stripWhiteSpace(str);
	tokens.push_back(str);

	return tokens;
}
*/

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
	program.open (filename);

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



Pcb createPCB(string filename, size_t numRegisters, unordered_set<unsigned int> *pids)
{
	// Initializes a Process Control Block using a "program" (.txt) file.
	unsigned int id = createId(pids);
	vector<string> program = readProgram(filename);
	string delim = ":";
	string name = delimitValue(program.at(0), delim);
	size_t burst = stoi(delimitValue(program.at(1), delim));
	uint64_t memory = stoi(delimitValue(program.at(2), delim));
	program.erase(program.begin(), program.begin() + 3);
	program.shrink_to_fit();

	return Pcb(id, name, burst, memory, program, numRegisters);
}


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

		default:
			cout << "Unknown error occurred!" << endl;
	}
	cout << "Shutting down..." << endl;
	exit(0);
}


int main()
{
	/*
	 * states:
	 * NEW – The program or process is being created or loaded (but not yet in memory).
	 * READY – The program is loaded into memory and is waiting to run on the CPU.
	 * RUN – Instructions are being executed (or simulated).
	 * WAIT (BLOCKED) – The program is waiting for some event to occur (such as an I/O completion).
	 * EXIT – The  program  has  finished  execution  on  the  CPU  (all  instructions  and I/O complete) and leaves memory.
	*/
	#define SIZE_MEMORY_MAIN 4294967296 // Represents size of main memory in bytes (4 GiB).
	#define SIZE_MEMORY_VIRTUAL 6442450944 // Represents size of virtual memory in bytes (6 GiB).
	#define SIZE_BACKING_STORE 1099511627776 // Represents size of backing store in bytes (1 TiB).
	#define SIZE_CACHE_CPU 1024 // Represents size of CPU cache in bytes (1 KiB).
	#define SIZE_BLOCK 4194304 // Represents size of paging block in bytes (4 MiB).

	// Main Memory
	Memory memoryMain = Memory(SIZE_MEMORY_MAIN); // @suppress("Ambiguous problem")

	// Tests memory for allocation.
	if (!memoryMain.memorySet)
	{
		close(1);
	}

	Memory *ptrMain = &memoryMain; // Points to memoryMain.

	uint64_t spaceMain = getAddressSpace(SIZE_MEMORY_MAIN); // Contains 2^29 space.
	cout << "main address space: " << spaceMain;
	cout << " bytes" << endl;

	uint64_t spaceVirtual = getAddressSpace(SIZE_MEMORY_VIRTUAL); // Contains 2^30 space.
	cout << "virtual address space: " << spaceVirtual;
	cout << " bytes" << endl;

	struct _test
	{
		int datum { 0 };
	};

	_test *test1 = new _test;
	test1->datum = 1;

	_test *test2 = new _test;
	test2->datum = 2;

	_test *test3 = new _test;
	test3->datum = 3;

	_test *test4 = new _test;
	test4->datum = 4;

	LinkedList<_test> linked = LinkedList<_test>();
	linked.add(test1);
	linked.add(test2);
	linked.add(test3);

	_test *test5 = linked.getStruct(1);

	cout << "test1: " << test1->datum << endl;
	cout << "test2: " << test2->datum << endl;
	cout << "test3: " << test3->datum << endl;
	cout << "test4: " << test4->datum << endl;

	if (test5 != 0)
	{
		cout << "test5: " << test5->datum << endl;
	}
	else
	{
		cout << "fail" << endl;
	}

	linked.fill(test4, 1);

	test5 = linked.getStruct(0);
	cout << "filled test5: " << test5->datum << endl;
	test5 = linked.getStruct(1);
	cout << "filled test5: " << test5->datum << endl;
	test5 = linked.getStruct(2);
	cout << "filled test5: " << test5->datum << endl;


	delete(test1);
	delete(test2);
	delete(test3);
	delete(test4);

	/*
	// Backing Store (Hard Disk Drive)
	Harddrive hdd = Harddrive(SIZE_BACKING_STORE);
	uint64_t spaceHarddrive = getAddressSpace(SIZE_BACKING_STORE); // 2^40 space
	cout << "harddrive address space: " << spaceHarddrive << endl;
	*/

	/*
	// Memory Management Unit
	Mmu mmu = Mmu(SIZE_BLOCK, spaceMain, spaceVirtual);
	uint64_t numFrames = mmu.getNumFrames();
	uint64_t numPages = mmu.getNumPages();
	cout << "frames (physical): " << numFrames << endl;
	cout << "pages (virtual): " << numPages << endl;
	*/

	/*
	// Central Processing Unit
	Cpu cpu = Cpu(SIZE_CACHE_CPU, ptrMain);
	int rCount = cpu.R_COUNT; // Holds number of registers.
	*/

	// Process Queues
	vector<Pcb> qJob;
	vector<Pcb> qReady;
	vector<Pcb> qDeviceIO;

	// Establishes operation codes that can be used.
	enum
	{
		OP_CALC = 0,
		OP_IO,
		OP_YIELD,
		OP_OUT
	};

	unordered_set<unsigned int> pids; // Holds set of all current Process IDs being used.
	unordered_set<unsigned int> *ptrPids = &pids;
	/*
	for (const unsigned int& x: pids)
	{
		cout << ", " << x;
	}
	cout << endl;
	*/

	/*
	string filename = "os_programs\\Text Processor.txt";
	Pcb pcb = createPCB(filename, rCount, ptrPids);
	qJob.push_back(pcb);*/

	//close();
	return 0;
};

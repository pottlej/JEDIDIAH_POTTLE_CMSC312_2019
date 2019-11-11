/*
 * main.cpp
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits.h> // UINT_MAX
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "cpu.h"
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

vector<string> readProgram(string filename)
{
	vector<string> text; // Contains program code.
	ifstream program;
	program.open (filename);

	while(!program.eof())
	{
		string line = "";
		getline(program, line);
		if (!line.empty())
		{
			text.push_back(line);
		}
	}
	program.close();
	text.shrink_to_fit();

	return text;
}

Pcb createPCB(string filename, unsigned int numRegisters, unordered_set<unsigned int> *pids)
{
	// Initializes a Process Control Block using a "program" (.txt) file.
	vector<string> program = readProgram(filename);
	string delim = ":";
	string name = delimitValue(program.at(0), delim);
	size_t burst = stoi(delimitValue(program.at(1), delim));
	uint64_t memory = stoi(delimitValue(program.at(2), delim));
	program.erase(program.begin(), program.begin() + 3);
	program.shrink_to_fit();

	return Pcb(name, burst, memory, numRegisters, pids, program);
}

void close()
{
	cout << "Good Bye :)" << endl;
	exit(0);
}


int main()
{
	#define SIZE_MEMORY_MAIN 4294967296 // Represents size of main memory in bytes (4096 MiB).
	#define SIZE_MEMORY_VIRTUAL 8589934592 // Represents size of virtual memory in bytes (8192 MiB).
	#define SIZE_CACHE_CPU 1024 // Represents size of CPU cache in bytes (1 KiB).
	#define SIZE_BLOCK 4194304 // Represents size of paging block in bytes (4 MiB).

	// Main Memory
	Memory memoryMain = Memory(SIZE_MEMORY_MAIN);
	Memory *ptrMain = &memoryMain;
	uint64_t spaceMain = memoryMain.getAddressSpace(); // 2^29 space
	cout << "main: " << spaceMain << endl;

	// Virtual Memory
	Memory memoryVirtual = Memory(SIZE_MEMORY_VIRTUAL);
	Memory *ptrVirtual = &memoryVirtual;
	uint64_t spaceVirtual = memoryVirtual.getAddressSpace(); // 2^30 space
	cout << "virtual: " << spaceVirtual << endl;

	// Memory Management Unit
	Mmu mmu = Mmu(spaceMain, spaceVirtual, SIZE_BLOCK);

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

	string filename = "programs\\Text Processor.txt";
	Pcb pcb = createPCB(filename, rCount, ptrPids);
	qJob.push_back(pcb);

	//close();
	return 0;
};

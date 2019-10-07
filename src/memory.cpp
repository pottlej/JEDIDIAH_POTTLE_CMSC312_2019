/*
 * memory.cpp
 */
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Memory
{
	private:
		vector<uint16_t> memory; // Represents memory locations which store 16-bit values each.

	// Default constructor
	Memory(long long int size)
	{
		setMemory(size);
	}

	private:
		void setMemory(long long int size)
		{
			// Calculates number of memory locations needed.
			int exp = ceil((log10(size / 16) / log10(2)));
			long long int numLocations = pow(2, exp);
			memory.resize(numLocations);
		}

	public:
		void write(uint16_t address, uint16_t instruction)
		{
		    memory[address] = instruction;
		}

		uint16_t read(uint16_t address)
		{
		    return memory[address];
		}
};




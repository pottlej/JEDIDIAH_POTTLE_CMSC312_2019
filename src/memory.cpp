/*
 * memory.cpp
 */
#include <cmath>
#include <cstdint>
#include <iostream>
using namespace std;

class Memory
{
	private:
		uint16_t* memory; // Represents memory locations which store 16-bit values each.

	public:
		// Default constructor
		Memory(long long int size)
		{
			setMemory(size);
		}

	private:
		void setMemory(long long int size)
		{
			// Calculates number of memory locations needed.
			int exp = ceil(log2(size/2));
			long long int numLocations = pow(2, exp);
			//cout << "locations: " << numLocations << endl;
			memory = new uint16_t[numLocations];
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




/*
 * memory.h
 */
#ifndef MEMORY_H_
#define MEMORY_H_
#include <cstdint>

class Memory
{
	private:
		uint64_t *memory { 0 }; // Holds memory locations.
		uint64_t space { 0 }; // Holds number of address locations

	public:
		Memory(); // Default constructor
		Memory(uint64_t size); // Parameter constructor
		~Memory(); // Deconstructor
		uint64_t getAddressSpace();
		void write(uint64_t address, uint64_t instruction);
		uint64_t read(uint64_t address);

	private:
		void setMemory(uint64_t size);
};

#endif /* MEMORY_H_ */

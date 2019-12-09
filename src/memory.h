/*
 * memory.h
 */
#ifndef MEMORY_H_
#define MEMORY_H_
#include <cstdint>

class Memory
{
	public:
		bool memorySet { 0 }; // State of memory setup.

	private:
		uint64_t *memory { 0 }; // Holds memory locations.

	public:
		Memory();
		Memory(uint64_t size);
		~Memory();
		void write(uint64_t address, uint64_t instruction);
		uint64_t read(uint64_t address);

	private:
		void setMemory(uint64_t size);
};

#endif /* MEMORY_H_ */

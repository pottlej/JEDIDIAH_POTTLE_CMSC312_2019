/*
 * memory.h
 *
 * Jedidiah Pottle
 * CMSC312
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
		uint64_t capacity { 0 };

	public:
		Memory(uint64_t size);
		~Memory();
		uint64_t getCapacity();
		void write(uint64_t address, uint64_t instruction);
		uint64_t read(uint64_t address);

	private:
		void setMemory(uint64_t size);
};

#endif /* MEMORY_H_ */

/*
 * cpu.h
 * Central Processing Unit
 */
#ifndef CPU_H_
#define CPU_H_
#include <cstdint>
#include <unordered_map>
#include "memory.h"

class Cpu
{
	public:
		// Establishes registers.
		enum
		{
			R_0 = 0,
			R_1,
			R_2,
			R_3,
			R_4,
			R_5,
			R_6,
			R_7,
			R_PC,
			R_COUNT
		};

	private:
		unsigned int *registers { 0 };

		// Establishes operation codes that can be used.
		enum
		{
			OP_CALC = 0,
			OP_IO,
			OP_YIELD,
			OP_OUT
		};

		std::size_t cacheSize { 0 };
		std::unordered_map<unsigned int, unsigned int> cache; // Translation Look-aside Buffer (TLB)
		Memory *memoryMain;

	public:
		Cpu(std::size_t cacheSize, Memory *memoryMain);
		~Cpu();
		void writeRegister(unsigned int registerId, unsigned int data);
		unsigned int readRegister(unsigned int registerId);
		void writeCache(unsigned int tag, unsigned int data);
		unsigned int readCache(unsigned int tag);
		void writeMemory(unsigned int address, unsigned int instruction);
		unsigned int readMemory(unsigned int address);

	private:
		void setCacheSize(size_t cacheSize);
		void setMemoryMain(Memory *memoryMain);
		void initRegisters();
		void calc();
		void io();
		void yield();
		void out();
};

#endif /* CPU_H_ */

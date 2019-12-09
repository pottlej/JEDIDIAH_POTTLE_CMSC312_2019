/*
 * cpu.h
 * Central Processing Unit
 */
#ifndef CPU_H_
#define CPU_H_
#include <cstdint>
#include <unordered_map>
#include "memory.h"
#include "mmu.h"

class Cpu
{
	public:
		// Establishes CPU registers.
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
		std::size_t cacheSize { 0 };
		std::unordered_map<uint64_t, uint64_t> cache; // Translation Look-aside Buffer (TLB)
		Memory *memoryMain;

	public:
		Cpu(std::size_t cacheSize, Memory *memoryMain);
		~Cpu();
		void writeRegister(unsigned int registerId, uint64_t instruction);
		unsigned int readRegister(unsigned int registerId);
		void writeCache(uint64_t tag, uint64_t instruction);
		uint64_t readCache(uint64_t tag);
		void writeMemory(uint64_t address, uint64_t instruction);
		uint64_t readMemory(uint64_t address);

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

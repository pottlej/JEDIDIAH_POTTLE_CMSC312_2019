/*
 * schedulerlong.cpp
 *
 * Jedidiah Pottle
 * CMSC312
 */
#include "schedulerlong.h"
using namespace std;

SchedulerLong::SchedulerLong(Memory *memoryMain)
{
	setMemoryMain(memoryMain);
}

void SchedulerLong::setReadyState(Pcb *pcb)
{
	pcb->setState(READY);
}

void SchedulerLong::movePcbToMemory(Pcb pcb)
{
	//Pcb pcb = getPcbFromDisk(pcb);
}

void SchedulerLong::setMemoryMain(Memory *memoryMain)
{
	this->memoryMain = memoryMain;
}

Pcb SchedulerLong::getPcbFromDisk(Pcb pcb)
{
	vector<uint64_t> text;
	uint64_t base = pcb.getBaseAddress();
	uint64_t limit = pcb.getLimitAddress();
	while (base <= limit)
	{
		//get hard drive address instructions
	}

	return pcb;
}

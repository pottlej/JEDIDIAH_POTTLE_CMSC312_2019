/*
 * schedulerlong.h
 *
 * Jedidiah Pottle
 * CMSC312
 */

#ifndef SCHEDULERLONG_H_
#define SCHEDULERLONG_H_
#include <vector>
#include "memory.h"
#include "pcb.h"

class SchedulerLong
{
	private:
		enum States
		{
			 NEW = 0, // The program or process is being created or loaded (but not yet in memory).
			 READY, // The program is loaded into memory and is waiting to run on the CPU.
			 RUN, // Instructions are being executed (or simulated).
			 WAIT, // (BLOCKED) The program is waiting for some event to occur (such as an I/O completion).
			 EXIT // The  program  has  finished  execution  on  the  CPU  (all  instructions  and I/O complete) and leaves memory.
		};

		Memory *memoryMain { 0 };

	public:
		SchedulerLong(Memory *memoryMain);
		void setReadyState(Pcb *pcb);
		void movePcbToMemory(Pcb pcb);

	private:
		void setMemoryMain(Memory *memoryMain);
		Pcb getPcbFromDisk(Pcb pcb);
};

#endif /* SCHEDULERLONG_H_ */

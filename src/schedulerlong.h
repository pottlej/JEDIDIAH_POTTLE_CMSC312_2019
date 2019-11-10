/*
 * schedulerlong.h
 */

#ifndef SCHEDULERLONG_H_
#define SCHEDULERLONG_H_
#include "pcb.h"

class SchedulerLong
{
	public:
		// Constructor
		SchedulerLong();
		void setReadyState(Pcb pcb);
		void changeQueues(std::vector<Pcb> from, std::vector<Pcb> to);
};

#endif /* SCHEDULERLONG_H_ */

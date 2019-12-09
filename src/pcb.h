/*
 * pcb.h
 * Process Control Block
 */

#ifndef PCB_H_
#define PCB_H_
//#include <cstdint>
#include <list>
#include <stack>
#include <string>
#include <time.h>
#include <unordered_set>
#include <vector>

class Pcb
{
	private:
		Pcb *parent { 0 };
		std::list<Pcb> childList; // List of children spawned by this process.
		unsigned int id { 0 };
		unsigned short state { 0 };
		bool critSection { 0 }; // Sets whether or not the process is in its critical section.
		uint64_t pc { 0 }; // Program Counter.
		unsigned short priority { 0 };
		std::string name { "" }; // Name of program.
		std::size_t burstTime { 0 };
		uint64_t memory { 0 }; // Amount of memory (in bytes) allocated to process.
		std::vector<std::string> text;
		uint64_t *registers { 0 }; // Contains register contents.
		std::vector<uint64_t> data; // Contains global variables.
		std::list<std::string> ioList; // IO devices allocated to process.
		std::list<std::string> fileList; // List of open files.
		std::stack<uint64_t> stack; // Stack containing temporary data such as function parameters, return addresses, and local variables.
		std::vector<uint64_t> heap; // Heap containing memory dynamically allocated during runtime.

	public:
		Pcb(unsigned int id, std::string name, std::size_t burst, uint64_t memory, std::vector<std::string> text, std::size_t numRegisters);
		~Pcb();
		void setId(unsigned int id);
		unsigned int getId();
		void setState(unsigned short s);
		unsigned short getState();
		void setCritSection(bool value);
		bool getCritSection();
		void setPC(uint64_t pc);
		uint64_t getPC();
		void setPriority(unsigned short pr);
		unsigned short getPriority();
		void setName(std::string name);
		std::string getName();
		void setBurstTime(std::size_t time); // Actual time (seconds): ((float)time)/CLOCKS_PER_SEC
		std::size_t getBurstTime();
		void setMemory(uint64_t amount);
		uint64_t getMemory();
		void setText(std::vector<std::string> text);
		std::vector<std::string> getText();
		std::string getTextLine(uint64_t line);
		void setData(std::vector<uint64_t> data);
		std::vector<uint64_t> getData();
		void ioListAdd(std::string element);
		void ioListRemove(std::string element);
		void ioListRemoveAll();
		bool ioListFind(std::string element);
		void fileListAdd(std::string element);
		void fileListRemove(std::string element);
		void fileListRemoveAll();
		bool fileListFind(std::string element);
		void stackPush(uint64_t value);
		void stackPop();
		uint64_t stackTop();
		void heapPush(uint64_t value);
		void heapPop();
		uint64_t heapFront();

	private:
		void initRegisters(size_t count);
		bool listAdd(std::list<std::string> container, std::string element);
		bool listRemove(std::list<std::string> container, std::string element);
		bool listRemoveAll(std::list<std::string> container);
		bool listFind(std::list<std::string> container, std::string element);
};

#endif /* PCB_H_ */

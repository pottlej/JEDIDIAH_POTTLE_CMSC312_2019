/*
 * pcb.cpp
 */
#include <algorithm>
#include <limits>
#include <list>
#include <stack>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

class Pcb
{
	private:
		unsigned int id;

		/*
		 * states:
		 * NEW – The program or process is being created or loaded (but not yet in memory).
		 * READY – The program is loaded into memory and is waiting to run on the CPU.
		 * RUN – Instructions are being executed (or simulated).
		 * WAIT (BLOCKED) – The program is waiting for some event to occur (such as an I/O completion).
		 * EXIT – The  program  has  finished  execution  on  the  CPU  (all  instructions  and I/O complete) and leaves memory.
		*/
		short state;
		int counter = 0x0000;
		int priority;
		int memory; // Amount of memory allocated to process
		int elapsedSeconds;
		list<string> ioList; // I/O devices allocated to process
		list<string> fileList;  // List of open files
		vector<uint16_t> registers; // Contains register contents.
		vector<string> text;
		vector<string> data; // Contains global variables
		stack<uint16_t> stack;  // Stack containing temporary data such as function parameters, return addresses, and local variables
		vector<uint16_t> heap; // Heap containing memory dynamically allocated during runtime

	// Default constructor
	Pcb(vector<string> text, int memoryAmount, int registerCount)
	{
		setId();
		setText(text);
		setMemory(memoryAmount);
		initRegisters(registerCount);
	}

	private:
		void setId()
		{
			unsigned int max = std::numeric_limits<unsigned int>::max();
			unsigned int val = rand() % max;
			id = val;
		}

		void setText(vector<string> text)
		{
			this->text = text;
		}

		void setMemory(int amount)
		{
			memory = amount;
		}

		void initRegisters(int count)
		{
			registers.resize(count);
		}
		/*
		void setTime()
		{

		}*/

	public:
		int getId()
		{
			return id;
		}

		void setState(short s)
		{
			state = s;
		}

		int getState()
		{
			return this->state;
		}

		void setCounter(int pc)
		{
			counter++;
		}

		int getCounter()
		{
			return counter;
		}

		void setPriority(int pr)
		{
			priority = pr;
		}

		int getPriority()
		{
			return priority;
		}

		void ioListAdd(string str) {
			ioList.insert(ioList.begin(), str);
		}

		void ioListRemove(string str) {
			ioList.remove(str);
		}

		void fileListAdd(string str) {
			fileList.insert(fileList.begin(), str);
		}

		void fileListRemove(string str) {
			fileList.remove(str);
		}

		vector<string> getText()
		{
			return text;
		}

		void setData(vector<string> data)
		{
			this->data = data;
		}

		vector<string> getData()
		{
			return data;
		}

		void stackPush(int v) {
			stack.push(v);
		}

		void stackPop() {
			stack.pop();
		}

		int stackTop() {
			return stack.top();
		}

		void heapPush(int v) {
			heap.push_back(v);
			if (!std::is_heap(heap.begin(), heap.end()))
				std::make_heap(heap.begin(), heap.end());
			std::push_heap(heap.begin(), heap.end());
		}

		void heapPop() {
			std::pop_heap(heap.begin(), heap.end());
			heap.pop_back();
		}

		int heapFront() {
			return heap.front();
		}
};



/*
 * pcb.cpp
 * Process Control Block
 */
#include <algorithm>
#include <iostream>
#include "pcb.h"
using namespace std;

// Public Members
Pcb::Pcb(unsigned int id, string name, size_t burst, uint64_t memory, vector<string> text, size_t numRegisters)
{
	setId(id);
	setName(name);
	setBurstTime(burst);
	setMemory(memory);
	setText(text);
	initRegisters(numRegisters);
}

Pcb::~Pcb()
{
	free(registers);
}

void Pcb::setId(unsigned int id)
{
	this->id = id;
}

unsigned int Pcb::getId()
{
	return id;
}

void Pcb::setState(unsigned short s)
{
	state = s;
}

unsigned short Pcb::getState()
{
	return state;
}

void Pcb::setCritSection(bool value)
{
	critSection = value;
}

bool Pcb::getCritSection()
{
	return critSection;
}

void Pcb::setPC(uint64_t pc)
{
	this->pc = pc;
}

uint64_t Pcb::getPC()
{
	return pc;
}

void Pcb::setPriority(unsigned short pr)
{
	priority = pr;
}

unsigned short Pcb::getPriority()
{
	return priority;
}

void Pcb::setName(std::string name)
{
	this->name = name;
}

std::string Pcb::getName()
{
	return name;
}

void Pcb::setBurstTime(size_t time)
{
	burstTime = time;
}

size_t Pcb::getBurstTime()
{
	return burstTime;
}

void Pcb::setMemory(uint64_t amount)
{
	memory = amount;
}

uint64_t Pcb::getMemory()
{
	return memory;
}

void Pcb::setText(vector<string> text)
{
	/*
	string* begin = text; // Stores beginning address of array.
	string* end = *(&text + 1); // Stores ending address of array.
	int size = end - begin;
	this->text = new string[size];
	copy(begin, end, this->text);
	*/
	this->text = text;
}

vector<string> Pcb::getText()
{
	return text;
}

string Pcb::getTextLine(uint64_t line)
{
	return text.at(line);
}

void Pcb::setData(vector<uint64_t> data)
{
	this->data = data;
}

vector<uint64_t> Pcb::getData()
{
	return data;
}

void Pcb::ioListAdd(string element)
{
	listAdd(ioList, element);
}

void Pcb::ioListRemove(string element)
{
	listRemove(ioList, element);
}

void Pcb::ioListRemoveAll()
{
	listRemoveAll(ioList);
}

bool Pcb::ioListFind(string element)
{
	return listFind(ioList, element);
}

void Pcb::fileListAdd(string element)
{
	listAdd(fileList, element);
}

void Pcb::fileListRemove(string element)
{
	listRemove(fileList, element);
}

void Pcb::fileListRemoveAll()
{
	listRemoveAll(fileList);
}

bool Pcb::fileListFind(string element)
{
	return listFind(fileList, element);
}

void Pcb::stackPush(uint64_t value)
{
	stack.push(value);
}

void Pcb::stackPop()
{
	stack.pop();
}

uint64_t Pcb::stackTop()
{
	return stack.top();
}

void Pcb::heapPush(uint64_t value)
{
	heap.push_back(value);
	if (!is_heap(heap.begin(), heap.end()))
	{
		make_heap(heap.begin(), heap.end());
	}
	push_heap(heap.begin(), heap.end());
}

void Pcb::heapPop()
{
	pop_heap(heap.begin(), heap.end());
	heap.pop_back();
}

uint64_t Pcb::heapFront()
{
	return heap.front();
}



// Private Members
void Pcb::initRegisters(size_t count)
{
	registers = (uint64_t*) calloc(count, sizeof(uint64_t));
}

bool Pcb::listAdd(list<string> container, string element)
{
	bool exists = listFind(container, element);
	if (!exists)
		container.insert(container.begin(), element);
	return exists;
}

bool Pcb::listRemove(list<string> container, string element)
{
	bool exists = listFind(container, element);
	if (exists)
		container.remove(element);
	return exists;
}

bool Pcb::listRemoveAll(list<string> container)
{
	container.erase(container.begin(), container.end());
	return container.empty();
}

bool Pcb::listFind(list<string> container, string element)
{
	bool found = (find(container.begin(), container.end(), element) != container.end());
	return found;
}



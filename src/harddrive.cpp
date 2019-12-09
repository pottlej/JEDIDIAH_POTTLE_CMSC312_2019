/*
 * harddrive.cpp
 */

#include <iostream>
#include "harddrive.h"
using namespace std;


HardDrive::HardDrive()
{
	head = new _address;
}

HardDrive::~HardDrive()
{
	_address *current = head;
	while (current->next != 0)
	{

	}
	delete(head);
}

uint64_t HardDrive::getAddress(uint64_t address)
{
	return 0;
}

void HardDrive::write(uint64_t address, uint64_t instruction)
{

}

uint64_t HardDrive::read(uint64_t address)
{
	return 0;
}


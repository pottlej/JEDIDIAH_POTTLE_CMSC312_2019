/*
 * linkedlist.cpp
 */

#include <iostream>
#include "linkedlist.h"
using namespace std;

template<typename Struct>
LinkedList<Struct>::LinkedList(){}

template<typename Struct>
LinkedList<Struct>::~LinkedList(){}

template<typename Struct>
Struct* LinkedList<Struct>::getStruct(uint64_t num)
{
	_node<Struct> *current;
	if (head != 0)
	{
		current = head;
		for (uint64_t i = 1; i <= num; i++)
		{
			if (current->next != 0)
			{
				current = current->next;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}

	return current->_data;
}

template<typename Struct>
void LinkedList<Struct>::add(Struct *data)
{
	_node<Struct> *temp = new _node<Struct>;
	temp->_data = data;

	if (head != 0)
	{
		_node<Struct> *current = head;
		while (current->next != 0)
		{
			current = current->next;
		}
		current->next = temp;
	}
	else
	{
		head = temp;
	}

	temp = 0;
	++listSize;
}

template<typename Struct>
void LinkedList<Struct>::fill(Struct *data, uint64_t pos)
{
	if (pos < listSize)
	{
		_node<Struct> *current = head;
		for (uint64_t i = 0; i < pos; i++)
		{
			current = current->next;
		}

		current->_data = data;
	}
}

template<typename Struct>
void LinkedList<Struct>::remove(Struct *data)
{

}

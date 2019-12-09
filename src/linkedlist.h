/*
 * linkedlist.h
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <cstdint>

template<typename Struct>
struct _node
{
	_node<Struct> *next { 0 };
	Struct *_data { 0 };
};

template<typename Struct>
class LinkedList
{
	private:
	_node<Struct> *head { 0 };
	uint64_t listSize { 0 }; // Number of list elements.

	public:
		LinkedList();
		~LinkedList();
		// Requires a check-for-zero to make sure the object is valid.
		Struct* getStruct(uint64_t num); // Gets the Struct object associated with the node number.
		void add(Struct *data); // Adds Struct object to LinkedList.
		// Overrides Struct object in specified position.
		void fill(Struct *data, uint64_t pos); // Fills specified position with Struct object.
		void remove(Struct *data); // Removes Struct object from LinkedList.
};

#include "linkedlist.cpp"
#endif /* LINKEDLIST_H_ */

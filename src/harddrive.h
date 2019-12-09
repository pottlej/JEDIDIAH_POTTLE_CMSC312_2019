/*
 * harddrive.h
 */

#ifndef HARDDRIVE_H_
#define HARDDRIVE_H_

struct _address
{
	_address *next { 0 };
	uint64_t instruction { 0 };
};

class HardDrive
{
	private:
	_address *head { 0 };

	public:
		HardDrive();
		~HardDrive();
		uint64_t getAddress(uint64_t address);
		void write(uint64_t address, uint64_t instruction);
		uint64_t read(uint64_t address);
};

#endif /* HARDDRIVE_H_ */

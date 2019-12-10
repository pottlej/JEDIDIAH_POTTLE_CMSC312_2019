/*
 * harddrive.h
 *
 * Jedidiah Pottle
 * CMSC312
 */

#ifndef HARDDRIVE_H_
#define HARDDRIVE_H_
#include <cstdint>
#include <fstream>
#include <set>
#include <string>

class HardDrive
{
	public:
		bool diskSet { 0 };

	private:
		uint64_t capacity { 0 };
		std::string filename { "os_harddrive.oshd" };
		std::fstream &harddrive;
		uint64_t numBlocks { 0 };

		// Keeps track of free blocks in ascending order.
		std::set<uint64_t, std::less<uint64_t>> freeBlocks { 0 };

	public:
		HardDrive(std::fstream &disk, uint64_t size, uint64_t blockSize);
		uint64_t getAddress(uint64_t address);
		uint64_t getCapacity();
		std::string getFilename();
		//bool writeId(uint64_t base, unsigned int id);
		bool write(uint64_t base, int offset, uint64_t instruction);
		uint64_t read(uint64_t address);
		uint64_t getFreeBlock();

	private:
		void setNumBlocks(uint64_t blockSize);
		uint64_t getLine(uint64_t address);
		uint64_t getLoc(uint64_t address, uint64_t instruction);
		bool fileExists(const std::string &filename);
		void addFreeBlock(uint64_t blockNum);
		void initHarddrive(); // Creates physical hard drive space.
		void resumeHarddrive(); // Resumes hard drive activity if already initialized.
};

#endif /* HARDDRIVE_H_ */

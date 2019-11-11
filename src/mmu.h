/*
 * mmu.h
 * Memory Management Unit
 */

#ifndef MMU_H_
#define MMU_H_
#include <unordered_map>

class Mmu
{
	public:
		uint64_t numFrames { 0 };
		uint64_t numPages { 0 };

	private:
		/*
		// Represents structure for a Page Table entry.
		typedef struct __pagetableentry{
			struct __pagetableentry *next;
			unsigned int pageNum;
			void *memoryAddress;
		}_PAGETABLEENTRY;
		*/
		std::unordered_map<int, std::pair<int, bool>> pageTable;

	public:
		Mmu(uint64_t physicalSpace, uint64_t virtualSpace, uint64_t blockSize);
		uint64_t getNumFrames();
		uint64_t getNumPages();

	private:
		void setNumFrames(uint64_t physicalSpace, uint64_t size);
		void setNumPages(uint64_t logicalSpace, uint64_t size);
};

#endif /* MMU_H_ */

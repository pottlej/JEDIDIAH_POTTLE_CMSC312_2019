/*
 * mmu.h
 * Memory Management Unit
 *
 * Jedidiah Pottle
 * CMSC312
 */

#ifndef MMU_H_
#define MMU_H_
#include <set>
#include <unordered_map>

class Mmu
{
	private:
		uint64_t numFrames { 0 };
		uint64_t numPages { 0 };

		// Represents structure for a Page Table entry.
		struct _page
		{
			struct _page *next { 0 };
			uint64_t pageNum { 0 };
			bool isVal { 0 }; // Valid or Invalid bit.
			bool isRef { 0 }; // Referenced bit.
			bool isMod { 0 }; // Modified bit.
			uint64_t baseAddress { 0 };
		};

		_page *pageTable { 0 };

		// Keeps track of free frames in ascending order.
		std::set<uint64_t, std::less<uint64_t>> freeFrames { 0 };

	public:
		Mmu(uint64_t blockSize, uint64_t physicalSpace, uint64_t logicalSpace);
		uint64_t getNumFrames();
		uint64_t getNumPages();
		void addPageData(uint64_t pageNum);
		void removePageData(uint64_t pageNum);

	private:
		void setNumFrames(uint64_t physicalSpace, uint64_t blockSize);
		void setNumPages(uint64_t logicalSpace, uint64_t blockSize);
		void initPageTable(uint64_t size);
		void addFreeFrame(uint64_t frameNum);
		uint64_t getFreeFrame();
};

#endif /* MMU_H_ */

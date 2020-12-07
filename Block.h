#pragma once
#include <utility>
#include <math.h>

class Block
{
	int numOccurances;			//amount of times the block appears in the loaded data set
	int yLevel[111] = { 0 };	//maps the number of occurances of each block on each y level (0 - 110)

	void mergeSort(std::pair<int, int>* input, int min, int max);
	void merge(std::pair<int, int>* toMerge, int min, int mid, int max);

	void quickSort(std::pair<int, int>* input, int min, int max);
	int partition(std::pair<int, int>* input, int min, int max);

public:
	Block();
	void addBlock(int yLevel);
	float PercentOverall(int numChunks);
	float PercentAtY(int yLevel, int numChunks);
	int numBlocksAt(int yMin, int yMax);

	int getNumOccurances();
	void clear();

	//--------------- Sorting Operations ---------------//
	// three sorting operations. Input is the y range in which we are sorting (k)
	// each sort returns a pair array, sorted in decending order
	// the pair.first is the yLevel, pair.second is the number at that yLevel

	// SELECTION SORT O(k^2)
	std::pair<int, int>* sortSelection(int yMin, int yMax);

	// QUICK SORT O(klogk), (O(logn) space complexity)
	std::pair<int, int>* sortQuick(int yMin, int yMax);
	
	// MERGE SORT O(klogk), (O(k) space complexity)
	std::pair<int, int>* sortMerge(int yMin, int yMax);
};


#include "Block.h"

Block::Block() { numOccurances = 0; }

void Block::addBlock(int y)
{
	numOccurances++;
	yLevel[y]++;
}

float Block::PercentOverall(int numChunks)
{
	//calculate the percent occupancy of a block in the entire data set
	// math is as follows:
		// 110 levels, 256 blocks per level * 100 for percentage
	
	return ((float)numOccurances / (110.0f * 256.0f * (float)numChunks)) * 100.0f;
}
float Block::PercentAtY(int level, int numChunks)
{
	//given a y-level, calculate the percent occupancy of a particular block
	// math is as follows:
		// 16 by 16 (or 256) blocks per level * numChunks * 100 for percentage
	return (float(yLevel[level]) / (256.0f * numChunks)) * 100.0f;
}

int Block::numBlocksAt(int yMin, int yMax)
{
	if (yMin == yMax)
		return yLevel[yMin];
	else
	{
		int total = 0;

		for (int i = yMin; i <= yMax; i++)
			total += yLevel[i];

		return total;
	}

	return 0;
}

int Block::getNumOccurances() { return numOccurances; }
void Block::clear()
{
	// set array values and occurances back to 0
	numOccurances = 0;

	for (int i = 0; i < 111; i++)
		yLevel[i] = 0;
}

// --------------- SELECTION SORT --------------- //
std::pair<int,int>* Block::sortSelection(int yMin, int yMax)
{
	// sort blocks using selection sort from greatest to smallest
	// given a range of y Levels (yMin to yMax), sort by smallest to greatest
	// create an output array of pairs to sort (yLevel, yValue)
	int size = yMax - yMin + 1;
	std::pair<int, int>* output = new std::pair<int, int>[size];

	for (int i = 0; i < size; i++)
	{
		output[i].first = yMin + i;
		output[i].second = yLevel[yMin + i];
	}

	// sort the pair* with selection sort
	for (int i = 0; i < size; i++)
	{
		int min = INT_MAX;
		int index = -1;
		for (int j = i; j < size; j++)
			if (output[j].second < min)
			{
				index = j;
				min = output[j].second;
			}

		// swap values
		std::pair<int, int> temp = output[index];
		output[index] = output[i];
		output[i] = temp;
	}

	return output;
}

// --------------- MERGE SORT --------------- //
std::pair<int, int>*Block::sortMerge(int yMin, int yMax)
{
	// create output array
	int size = yMax - yMin + 1;
	std::pair<int, int>* output = new std::pair<int, int>[size];

	for (int i = 0; i < size; i++)
	{
		output[i].first = yMin + i;
		output[i].second = yLevel[yMin + i];
	}

	// call to merge recursive function
	mergeSort(output, 0, size - 1);

	return output;
}
void Block::mergeSort(std::pair<int, int>* input, int min, int max)
{
	// continue to merge if min is still less than max
	if (min < max)
	{
		// create a midpoint to split array
		int midInd = min + ((max - min) / 2);

		// call the sort function again for the left and right sub arrays
		mergeSort(input, min, midInd);
		mergeSort(input, midInd + 1, max);

		// merge arrays
		merge(input, min, midInd, max);
	}
}
void Block::merge(std::pair<int, int>* toMerge, int min, int midInd, int max)
{
	// create two sub arrays to store values
	// merge back into the toMerge array

	int minSize = midInd - min + 1;
	int maxSize = max - midInd;

	// temp sub arrays
	std::pair<int, int>* minArr = new std::pair<int, int>[minSize];
	std::pair<int, int>* maxArr = new std::pair<int, int>[maxSize];


	// add values AND yLevels
	for (int i = 0; i < minSize; i++)
	{
		minArr[i].first = toMerge[min + i].first;
		minArr[i].second = toMerge[min + i].second;
	}
	for (int i = 0; i < maxSize; i++)
	{
		maxArr[i].first = toMerge[midInd + i + 1].first;
		maxArr[i].second = toMerge[midInd + i + 1].second;
	}

	// merge!! in ascending order
	// left(min), right(max), and main index location
	int l = 0;
	int r = 0;
	int index = min;

	while (l < minSize && r < maxSize)
	{
		if (minArr[l].second < maxArr[r].second)
		{
			toMerge[index] = minArr[l];
			l++;
		}
		else
		{
			toMerge[index] = maxArr[r];
			r++;
		}

		index++;
	}

	// dump in the rest of either array to the toMerge array
	while (l < minSize)
	{
		toMerge[index] = minArr[l];
		l++;
		index++;
	}
	while (r < maxSize)
	{
		toMerge[index] = maxArr[r];
		r++;
		index++;
	}

	// deallocate heap arrays
	delete[] minArr;
	delete[] maxArr;
}

// --------------- QUICK SORT --------------- //
std::pair<int, int>* Block::sortQuick(int yMin, int yMax) {
	// create output array
	int size = yMax - yMin + 1;
	std::pair<int, int>* output = new std::pair<int, int>[size];

	for (int i = 0; i < size; i++)
	{
		output[i].first = yMin + i;
		output[i].second = yLevel[yMin + i];
	}

	//call to quickSort function
	quickSort(output, 0, size - 1);

	return output;
}
void Block::quickSort(std::pair<int, int>* input, int min, int max) {
	if (min < max)
	{
		//partIndex is the partition index, or index that divides the array to be sorted
		//puts input[partIndex] in correct spot
		int partIndex = partition(input, min, max);

		// Sort elements before index
		quickSort(input, min, partIndex - 1);
		//Sort elements after index
		quickSort(input, partIndex + 1, max);
	}
}
int Block::partition(std::pair<int, int>* input, int min, int max) {
	//takes last element in array and places it in its correct position
	//moves all elements smaller than pivot to the left and larger elements to the right
	int pivot = input[max].second; // pivot element (last element)
	int i = (min - 1); // Index of smaller element

	for (int j = min; j <= max - 1; j++)
	{
		// If current element is smaller than the pivot
		if (input[j].second < pivot)
		{
			i++; // increment index of smaller element
			swap(input[i], input[j]);
		}
	}
	swap(input[i + 1], input[max]);
	return (i + 1);
}
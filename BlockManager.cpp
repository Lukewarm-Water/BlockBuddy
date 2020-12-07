#include "BlockManager.h"

BlockManager::BlockManager()
{
	// push in block names
	blockNames[0] = "Air";
	blockNames[1] = "Stone";
	blockNames[2] = "Grass";
	blockNames[3] = "Dirt";
	blockNames[4] = "Gravel";
	blockNames[5] = "Wood/Bark";
	blockNames[6] = "Leaves";
	blockNames[7] = "Granite";
	blockNames[8] = "Diorite";
	blockNames[9] = "Andesite";
	blockNames[10] = "Coal Ore";
	blockNames[11] = "Iron Ore";
	blockNames[12] = "Gold Ore";
	blockNames[13] = "Redstone Ore";
	blockNames[14] = "Lapis Lazuli";
	blockNames[15] = "Diamond Ore";
	blockNames[16] = "Bedrock";
}

void BlockManager::initializeChunks(int numChunks)
{
	//load raw data in
	std::vector<int*> output = generator.loadChunks(numChunks);
	chunks = numChunks;

	//someIndex = (currYPos * 256) + (currZPos * 16) + currXPos
	//syntax will thus become output[chunkNum][someIndex]
	for (int chunkNum = 0; chunkNum < numChunks; chunkNum++)
		for (int y = 0; y <= 110; y++)
			for (int z = 0; z < 16; z++)
				for (int x = 0; x < 16; x++)
					blocks[output[chunkNum][(y * 256) + (z * 16) + x]].addBlock(y);

	/*
	std::pair<int, int>* sort = blocks[10].sortQuick(3, 6);
	std::vector<std::pair<int, int>> test;

	for (int i = 0; i < 4; i++)
	{
		std::pair<int, int> temp = sort[i];
		test.push_back(temp);
	}
	*/

	// deallocate space on heap from the generator
	for (int i = 0; i < output.size(); i++)
		delete[] output[i];
}

void BlockManager::PrintOverviewData(bool dispOre, bool dispStone, bool dispWood, bool dispOther, bool mostCommon)
{
	// sort data depending on which sort type is active
	// (1) SELECTION, (2) QUICK SORT, (3) MERGE SORT
	std::vector<std::pair<int, int>*> sortedBlocks;

	for (int i = 0; i <= 16; i++)
	{
		switch (sortType)
		{
		case 1:
			sortedBlocks.push_back(blocks[i].sortSelection(0, 110));
			break;
		case 2:
			sortedBlocks.push_back(blocks[i].sortQuick(0, 110));
			break;
		case 3:
			sortedBlocks.push_back(blocks[i].sortMerge(0, 110));
			break;
		}
	}

	std::cout	<< "-------Block Overview------\n"
				<< "Total blocks analyzed: " << chunks * 28416 << "\n\n";

	// loop through all block types, display each occurances, percentages, and common y-level
	for (int i = 0; i <= 16; i++)
	{
		// big if-statement that checks to see if the current block should be displayed
		if ((dispOre && i >= 10 && i <= 15)
			|| (dispStone && i == 1)
			|| (dispWood && i == 5)
			|| (dispOther && (!((i == 1) || (i == 5) || (i >=10 && i<= 15)))))
		{
			// grass only appears on one y-level, so do not include 5 top choices
			// only display 3 levels for bedrock, as it only exists on 5 levels
			if (i == 2)
				displayBlock(i, mostCommon, sortedBlocks, 1, 111, blocks[i].getNumOccurances());
			else if (i == 16)
				displayBlock(i, mostCommon, sortedBlocks, 3, 111, blocks[i].getNumOccurances());
			else
				displayBlock(i, mostCommon, sortedBlocks, 5, 111, blocks[i].getNumOccurances());
			
			std::cout << "\n";
		}
	}

	// deallocate sorted data
	for (int i = 0; i < sortedBlocks.size(); i++)
		delete[] sortedBlocks[i];
}

void BlockManager::PrintYRange(int lowerY, int upperY)
{
	// sort data depending on which sort type is active
	// (1) SELECTION, (2) QUICK SORT, (3) MERGE SORT
	std::vector<std::pair<int, int>*> sortedBlocks;

	std::cout << "-------Examining Y-Levels " << lowerY << " to " << upperY << "------\n\n";

	for (int i = 0; i <= 16; i++)
	{
		switch (sortType)
		{
		case 1:
			sortedBlocks.push_back(blocks[i].sortSelection(lowerY, upperY));
			break;
		case 2:
			sortedBlocks.push_back(blocks[i].sortQuick(lowerY, upperY));
			break;
		case 3:
			sortedBlocks.push_back(blocks[i].sortMerge(lowerY, upperY));
			break;
		}
	}

	// size of each pair array
	int rangeSize = upperY - lowerY + 1;

	// only display blocks that do not have a count of 0 within this y-level range
	// display the most common y-levels as well. Display 1, 3, or 5 levels depending on the size of the range
	for (int i = 0; i <= 16; i++)
	{
		int numBlocks = blocks[i].numBlocksAt(lowerY, upperY);

		if (numBlocks != 0)
		{
			if (rangeSize <= 3)
				displayBlock(i, true, sortedBlocks, 1, rangeSize, numBlocks);
			else if (rangeSize > 3 && rangeSize <= 7)
				displayBlock(i, true, sortedBlocks, 3, rangeSize, numBlocks);
			else if (rangeSize > 7)
				displayBlock(i, true, sortedBlocks, 5, rangeSize, numBlocks);

			percentYRange(i, lowerY, upperY);
		}
	}


	// deallocate sorted data
	for (int i = 0; i < sortedBlocks.size(); i++)
		delete[] sortedBlocks[i];
}
void BlockManager::PrintYLevel(int y)
{
	// display the stats of all blocks on the y level, along with its frequency percentage
	// incude a "most common" block
		// disregard, stones, dirts, and gravels for this (only use ores or wood/leaves)

	std::cout << "-------Examining Y-Level " << y << "------\n\n";

	int maxBlock = 0;
	for (int i = 0; i <= 16; i++)
	{
		if (blocks[i].numBlocksAt(y, y) != 0)
		{
			std::cout
				<< blockNames[i] << " (ID - " << i << "):\n"
				<< "Occurances: " << blocks[i].numBlocksAt(y, y) << "\n"
				<< "   This block makes up " << blocks[i].PercentAtY(y, chunks) << "% of Y-Level " << y << ".\n";
		}

		// check to see if current block is an ore/wood, and if its more common than current maxBlock
		if ((i >= 10 && i <= 15) || i == 5)
			if (blocks[i].numBlocksAt(y, y) > blocks[maxBlock].numBlocksAt(y, y))
				maxBlock = i;
	}

	// display a most common ore (if one exists)
	if (maxBlock != 0)
	{
		std::cout << "\nThus, the most common unique block on this Y-Level is " << blockNames[maxBlock] << "\n\n";
	}
	else
		std::cout << "\nThe most common block on this Y-Level is Stone\n\n";

}
void BlockManager::PrintSingleBlock(int blockID)
{
	// sort data depending on which sort type is active
	// (1) SELECTION, (2) QUICK SORT, (3) MERGE SORT
	std::vector<std::pair<int, int>*> sortedBlocks;

	for (int i = 0; i <= 16; i++)
	{
		switch (sortType)
		{
		case 1:
			sortedBlocks.push_back(blocks[i].sortSelection(0, 110));
			break;
		case 2:
			sortedBlocks.push_back(blocks[i].sortQuick(0, 110));
			break;
		case 3:
			sortedBlocks.push_back(blocks[i].sortMerge(0, 110));
			break;
		}
	}

	std::cout
		<< "-------Statistics For " << blockNames[blockID] << "------\n\n"
		<< "Total Number of Occurances: " << blocks[blockID].getNumOccurances() << "\n"
		<< "% of chunks loaded: " << blocks[blockID].PercentOverall(chunks) << "%\n\n";

	std::cout
		<< "----Y-Level Statistics by Frequency----\n";

	// print occurances on each y-level along with percentage of it at that level
	for (int i = 0; i < 111; i++)
	{
		std::pair<int, int>& temp = sortedBlocks[blockID][110 - i];
		if (temp.second != 0)
			std::cout
				<< "Y-Level " << temp.first << ":\n"
				<< "   Occurances: " << temp.second << "\n"
				<< "   This block makes up " << blocks[blockID].PercentAtY(temp.first, chunks) << "% of the blocks at this y-Level\n";
	}

	std::cout << "\n";

	// deallocate sorted data
	for (int i = 0; i < sortedBlocks.size(); i++)
		delete[] sortedBlocks[i];
}

void BlockManager::setSortingType(int type) { sortType = type; }

float BlockManager::overallPercent(std::pair<int, int>* sortedLevels, int size, int numLevels, int blockID)
{
	int numBlocks = 0;
	for (int i = 0; i < numLevels; i++)
		numBlocks += sortedLevels[size - i - 1].second;

	float total = (float)numBlocks / (float)blocks[blockID].getNumOccurances();
	return total * 100.0f;
}
void BlockManager::percentYRange(int blockID, int min, int max)
{
	// sum all percentages of a block over Y Range
	float totalPercent = 0.0f;
	for (int i = min; i <= max; i++)
		totalPercent += blocks[blockID].PercentAtY(i, chunks);

	// divide percentages by size of the y-level range to get range-percentage
	float toDivide = max - min + 1;
	totalPercent /= toDivide;

	std::cout
		<< "   This block makes up " << totalPercent << "% of the Y-Levels examined\n\n";
}
void BlockManager::displayBlock(int blockID, bool mostCommon, std::vector<std::pair<int, int>*>& sortedBlocks, int numLevels, int size, int occurances)
{
	std::cout
		<< blockNames[blockID] << " (ID - " << blockID << "):\n"
		<< "Occurances: " << occurances << "\n"
		<< "% of chunks loaded: " << blocks[blockID].PercentOverall(chunks) << "%\n";

	if (mostCommon)
	{
		std::cout << "Most commonly found Y-levels: ";
		std::cout << sortedBlocks[blockID][size - 1].first;

		for (int i = 1; i < numLevels; i++)
			std::cout << ", " << sortedBlocks[blockID][size - i - 1].first;
		std::cout << "\n";

		std::cout
			<< "   these Y-levels constitute " << overallPercent(sortedBlocks[blockID], size, numLevels, blockID)
			<< "% of the overall number of " << blockNames[blockID] << " blocks\n";
	}
	else
	{
		std::cout << "Least commonly found Y-levels: ";

		int counter = 0;
		for (int i = 0; i < size; i++)
		{
			if (sortedBlocks[blockID][i].second != 0)
			{
				std::cout << sortedBlocks[blockID][i].first;
				counter++;

				// formatting commas
				if (counter != numLevels && i != 110)
					std::cout << ", ";
			}
			if (counter == numLevels)
				break;
		}

		std::cout << "\n";
	}
}

void BlockManager::clearBlockData()
{
	// clear data within each block object for reloading chunks
	for (int i = 0; i <= 16; i++)
		blocks[i].clear();
}
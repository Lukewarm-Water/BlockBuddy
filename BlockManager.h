#pragma once
#include "Block.h"
#include "BlockGen.h"
#include <vector>
#include <unordered_map>

class BlockManager
{
	//primary container for holding our organized data, and another map that correlates to name
	std::unordered_map<int, Block> blocks;
	std::unordered_map<int, std::string> blockNames;

	// generator to create blocks
	BlockGen generator;

	// sorting type (1 - 3) depending on below sorts
	int sortType = 1;

	// number of chunks loaded
	int chunks = -1;
	
	/*
	~~~~~KEY REFERENCE~~~~
	0: Air
	1: Stone
	2: Grass
	3: Dirt
	4: Gravel
	5: Wood/Bark
	6: Leaves
	7: Granite
	8: Diorite
	9: Andesite
	10: Coal Ore
	11: Iron Ore
	12: Gold Ore
	13: Redstone Ore
	14: Lapis Lazuli
	15: Diamond Ore
	16: Bedrock
	*/


	// ----------------- helper functions ----------------- //
	float overallPercent(std::pair<int, int>* sortedLevels, int size, int numLevels, int blockID);
	void percentYRange(int blockID, int min, int max);
	void displayBlock(int blockID, bool mostCommon, std::vector<std::pair<int, int>*>& sortedBlocks, int numLevels, int size, int occurances);

public:
	BlockManager();
	void initializeChunks(int numChunks);

	void PrintOverviewData(bool dispOre, bool dispStone, bool dispWood, bool dispOther, bool mostCommon);
	void PrintYRange(int lowerY, int upperY);
	void PrintYLevel(int y);
	void PrintSingleBlock(int blockID);

	void setSortingType(int type);

	void clearBlockData();
};


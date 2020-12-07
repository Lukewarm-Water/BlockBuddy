#pragma once
#include "Random.h"
#include <unordered_map>
#include <vector>
#include <iostream>

class BlockGen
{
	// some comments on block generation:
	// because attempting to store blocks objects in these may result in way too much space, the following formate will be used
	// a blockTag (which we will make up for simplicity instead of using Minecraft's actual tags) to represent what block it correlates to
	
	// 0 = air, 1 = stone, 2 = grass, 3 = dirt, 4 = gravel, 5 = wood/bark, 6 = leaves, 7 = granite, 8 = diorite, 9 = andesite
	// 10 = coal, 11 = iron, 12 = gold, 13 = redstone, 14 = lapis lazuli, 15 = diamond, 16 = bedrock
	
	// y @ 0
		// bedrock
	// y @ 1-5
		// coal (map 0-5 to 0-1.25%), redstone (map 0-5 to 0-1.0%), iron (map 0-5 to 0-0.75%), 
		// gold (map 0-5 to 0-0.15%), diamond (map 0-5 to 0-0.11%), lapis lazuli (map 0-15 to 0-0.10%)
		// rest otherStone/dirt
	// y @ 6-15
		// coal (map 5-60 to 1.25-1.00%), redstone (1.00%), iron (0.75%), gold (0.15%), diamond (0.11%), lapis lazuli (map 0-15 to 0-0.10%)
		// rest otherStone/dirt
	// y @ 16-30
		// coal (map 5-60 to 1.25-1.00%), iron (0.75%), gold (0.15%), lapis lazuli (map 15-30 to 0.10-0%)
		// rest otherStone/dirt
	// y @ 31 - 60 
		// coal (map 5-60 to 1.25-1.00%), iron (0.75%)
		// rest otherStone/dirt
	// y @ 61 - 70
		// coal (map 60-70 to 1.00-0.30%), iron (map 60-70 to 0.75-0%)
		// rest otherStone/dirt
	// y @ 71 - 80 (im making 80 the default surface for simplicity)
		// coal (map 70-80 to 0.30%-0.20%)
		// rest otherStone/dirt
	// y @ 81 - 84
		// dirt 100%
	// y @ 85
		// grass 100%
	// y @ 86 - 90
		// wood 5%, leaves 3%, other AIR
	// y @ 91 - 100
		// leaves (map 90-100 to 5-10%), other AIR
	// y > 100
		// AIR
	
	// for simplicity, even though chunks go up to 256, we will stop at y = 110
	// in terms of otherStone/dirt calcualtions
		// 80% stone, 10% dirt, 3.34% andesite, 3.33% diorite, 3.33% granite

	std::unordered_map<int, int> blockToNum;

	int getBlock(int yLevel);
	int* loadChunk();
	int pickStone();
	float mapVal(int input, int start1, int end1, float start2, float end2);
	void printStats();

public:
	BlockGen();
	std::vector<int*> loadChunks(int numChunks);
	std::vector<int*> performStartup();
};


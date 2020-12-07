#include "BlockGen.h"
using std::cout;
using std::endl;

BlockGen::BlockGen() {}

std::vector<int*> BlockGen::performStartup()
{
	// README:
	//	feel free to remove most of this setup and include it in the main file you have
	int numChunks = 0;
	cout << "Enter a number of chunks to generate: ";
	std::cin >> numChunks;

	cout << "Loading chunks... " << endl;

	// you can use this function to load the input chunks
	std::vector<int*> output = loadChunks(numChunks);

	cout << "Loaded! Would you like to see stats? (y/n)" << endl;

	char response = 'n';
	std::cin >> response;

	// see printStats() for description
	if (response == 'y')
		printStats();

	return output;
}

std::vector<int*> BlockGen::loadChunks(int numChunks)
{
	// initialize vector
	// return value is not a pointer/reference because numChunks holds pointers
	std::vector<int*> output;

	for (int i = 0; i < numChunks; i++)
		output.push_back(loadChunk());
	return output;
}

void BlockGen::printStats()
{
	// this is mostly for debugging purposes
	cout
		<< "Air: " << blockToNum[0] << endl
		<< "Stone: " << blockToNum[1] << endl
		<< "Grass: " << blockToNum[2] << endl
		<< "Dirt: " << blockToNum[3] << endl
		<< "Gravel: " << blockToNum[4] << endl
		<< "Wood/Bark: " << blockToNum[5] << endl
		<< "Leaves: " << blockToNum[6] << endl
		<< "Granite: " << blockToNum[7] << endl
		<< "Diorite: " << blockToNum[8] << endl
		<< "Andesite: " << blockToNum[9] << endl
		<< "Coal: " << blockToNum[10] << endl
		<< "Iron: " << blockToNum[11] << endl
		<< "Gold: " << blockToNum[12] << endl
		<< "Redstone: " << blockToNum[13] << endl
		<< "Lapis Lazuli: " << blockToNum[14] << endl
		<< "Diamond: " << blockToNum[15] << endl
		<< "Bedrock: " << blockToNum[16] << endl;
}

int* BlockGen::loadChunk()
{
	// initialize output on the heap
	// 111 y-levels (0 included), 16 z-values, 16 x-values
	int* output = new int[28416];

	// the blocks in the array will be stored as follows:
		// someIndex = (currYPos * 256) + (currZPos * 16) + currXPos

	for (int y = 0; y <= 110; y++)
		for (int z = 0; z < 16; z++)
			for (int x = 0; x < 16; x++)
			{
				int block = getBlock(y);

				// make sure math isnt wrong (a catch-all)
				if ((y * 256) + (z * 16) + x > 28415)
					cout << "error, managed to go out of bounds";
				else
					output[(y * 256) + (z * 16) + x] = block;

				// for debugging purposes, increments each key's value of the associated block
				blockToNum[block]++;
			}

	return output;
}

// uses a lot of percentages and the Random.cpp class to generate random floats
// floats are used to determine the block time (which is also split up into the pick stone function
int BlockGen::getBlock(int yLevel)
{
	if (yLevel == 0)
		return 16;
	if (yLevel > 100)
		return 0;
	if (yLevel <= 84 && yLevel >= 81)
		return 3;
	if (yLevel == 85)
		return 2;

	if (yLevel <= 5)
	{
		// generate ranges for each value
		// add prev value so each value has like a 'range'
		float coal = mapVal(yLevel, 0, 5, 0.0f, 1.25f);
		float redstone = coal + mapVal(yLevel, 0, 5, 0.0f, 1.0f);
		float iron = redstone + mapVal(yLevel, 0, 5, 0.0f, 0.75f);
		float gold = iron + mapVal(yLevel, 0, 5, 0.0f, 0.15f);
		float diamond = gold + mapVal(yLevel, 0, 5, 0.0f, 0.11f);
		float lapis = diamond + mapVal(yLevel, 0, 15, 0.0f, 0.10f);
		float bedrock = lapis + mapVal(yLevel, 1, 4, 20.0f, 0.0f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		if (rand < redstone)
			return 13;
		if (rand < iron)
			return 11;
		if (rand < gold)
			return 12;
		if (rand < diamond)
			return 15;
		if (rand < lapis)
			return 14;
		if (rand < bedrock)
			return 16;
		else
			return pickStone();
	}

	if (yLevel <= 15)
	{
		float coal = mapVal(yLevel, 5, 60, 1.25f, 1.00f);
		float redstone = coal + 1.00f;
		float iron = redstone + 0.75f;
		float gold = iron + 0.15f;
		float diamond = gold + 0.11f;
		float lapis = diamond + mapVal(yLevel, 0, 15, 0.0f, 0.10f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		if (rand < redstone)
			return 13;
		if (rand < iron)
			return 11;
		if (rand < gold)
			return 12;
		if (rand < diamond)
			return 15;
		if (rand < lapis)
			return 14;
		else
			return pickStone();
	}

	if (yLevel <= 30)
	{
		float coal = mapVal(yLevel, 5, 60, 1.25f, 1.00f);
		float iron = coal + 0.75f;
		float gold = iron + 0.15f;
		float lapis = gold + mapVal(yLevel, 15, 30, 0.10f, 0.0f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		if (rand < iron)
			return 11;
		if (rand < gold)
			return 12;
		if (rand < lapis)
			return 14;
		else
			return pickStone();
	}

	if (yLevel <= 60)
	{
		float coal = mapVal(yLevel, 5, 60, 1.25f, 1.00f);
		float iron = coal + 0.75f;

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		if (rand < iron)
			return 11;
		else
			return pickStone();
	}

	if (yLevel <= 70)
	{
		float coal = mapVal(yLevel, 60, 70, 1.00f, 0.30f);
		float iron = coal + mapVal(yLevel, 60, 70, 0.75f, 0.0f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		if (rand < iron)
			return 11;
		else
			return pickStone();
	}

	if (yLevel <= 80)
	{
		float coal = mapVal(yLevel, 70, 80, 0.30f, 0.20f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < coal)
			return 10;
		else
			return pickStone();
	}

	if (yLevel <= 90)
	{
		float wood = 5.0f;
		float leaves = wood + 3.0f;

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < wood)
			return 5;
		if (rand < leaves)
			return 6;
		else
			return 0;
	}

	if (yLevel <= 100)
	{
		float leaves = mapVal(yLevel, 90, 100, 5.0f, 10.0f);

		float rand = Random::Float(0.0f, 100.0f);

		if (rand < leaves)
			return 6;
		else
			return 0;
	}
}

// basically the map() function from Processesing so I can map values by y-level to make a slightly more dynamic percentage generation
float BlockGen::mapVal(int input, int start1, int end1, float start2, float end2)
{
	// given an imput that ranges from start2 to end 1
	// map it to a location in start2 end2
	float output = start2 + ((float)input - (float)start1) * ((end2 - start2) / ((float)end1 - (float)start1));
	return output;
}

// if pickStone() is chosen from getBlock(), it does another round of random number gen to pick the type of stone
// includes: stone, dirt, gravel, andesite, diorite, granite
int BlockGen::pickStone()
{
	// in terms of otherStone/dirt calcualtions
		// 55% stone, 8% dirt, 7% gravel, 10% andesite, 10% diorite, 10% granite

	float rand = Random::Float(0.0f, 100.0f);

	if (rand < 55)
		return 1;
	if (rand < 63)
		return 3;
	if (rand < 70)
		return 4;
	if (rand < 80)
		return 9;
	if (rand < 90)
		return 8;
	else
		return 7;
}
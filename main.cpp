#include "BlockManager.h""
#include <iostream>
#include <vector>
#include <string>
using namespace std;
   
// single global object. While global variables aren't ideal, this object is being used by all functions below
// thus, it saves the need to pass by reference in each function
BlockManager chunkData;

void PrintMenu();
void ChunkOverviewMode();
void SingleBlockMode();
void YLevelMode();
void PrintCheckbox(bool isChecked);
string filterInput(string input, int lower, int upper);

int main()
{
    // everything is done an managed in the printMenu() function
    PrintMenu();
    return 0;
}

void PrintMenu()
{
    // clear block data when new chunks are loaded
    chunkData.clearBlockData();

    string input;

    cout << string(50, '\n');
    cout << "~~~~~~~~~~~~~~~~~~~~~WELCOME TO BLOCK BUDDY!~~~~~~~~~~~~~~~~~~~~~\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "                           +--------+\n"
        << "                          /        /|\n"
        << "                         +--------+ |\n"
        << "                         |        | |\n"
        << "                         |        | +\n"
        << "                         |        |/\n"
        << "                         +--------+\n"
        << "We are here to help you analyze chunks to help you identify patterns and properties of common blocks!\n\n"
        << "First off, how many chunks would you like to load? (One chunk is 16x16x256 blocks)\n"
        << "Enter a number: ";
    cin >> input;
    input = filterInput(input, 1, 100);
    cout << string(50, '\n');

    cout << "\n\nLoading " << stoi(input) * 16 * 16 * 111 << " blocks, please wait a moment . . .\n\n" << endl;

    chunkData.initializeChunks(stoi(input));

    cout << "Phew! That was a lot of blocks, but nothing a computer can\'t handle!\n"
        << "Which type of sorting would you like to do?\n"
        << "( 1 ) Selection Sorting\n"
        << "( 2 ) Quick Sort\n"
        << "( 3 ) Merge Sorting\n"
        << "Please enter 1, 2, or 3: ";

    cin >> input;
    input = filterInput(input, 1, 3);
    chunkData.setSortingType(stoi(input));

    cout << "\nNow, how would you like to analyze your chunks?\n"
         << "( 1 ) Chunk Overview Mode\n"
         << "( 2 ) Analyze Y-Level\n"
         << "( 3 ) Analyze Single Block\n"
         << "Please enter 1, 2, or 3: ";
    cin >> input;
    input = filterInput(input, 1, 3);
    cout << endl << endl;

    if (stoi(input) == 1)
        ChunkOverviewMode();
    else if (stoi(input) == 2)
        YLevelMode();
    else if (stoi(input) == 3)
        SingleBlockMode();
}

void ChunkOverviewMode()
{
    string input = "-1";

    //checkbox variables
    bool dispOre = true;
    bool dispStone = true;
    bool dispWood = true;
    bool dispOther = true;
    bool mostCommon = true;

    cout << string(50, '\n');
    cout << "~~~~~~~~~~ CHUNK OVERVIEW MODE ~~~~~~~~~~" << endl;

    while (stoi(input) != 0)
    { 
        cout << "---------------------------------Filters------------------------------------\n"
            << "Display:" << endl;
        PrintCheckbox(dispOre);
        cout << " Ore (1)" << endl;

        PrintCheckbox(dispStone);
        cout << " Stone (2)" << endl;

        PrintCheckbox(dispWood);
        cout << " Wood (3)" << endl;

        PrintCheckbox(dispOther);
        cout << " Other (4)" << endl << endl;

        cout << "Sort:" << endl;
        PrintCheckbox(mostCommon);
        cout << " Most Common (5)" << endl;

        PrintCheckbox(!mostCommon);
        cout << " LeastCommon (6)" << endl << endl;

        cout << "(0) Print using current settings\n\n"
            << "Please enter a number associated with the filter options: ";
        cin >> input;
        input = filterInput(input, 0, 6);
        cout << string(50, '\n');

        if (stoi(input) == 1)
        {
            if (dispOre)
                dispOre = false;
            else
                dispOre = true;
        }
        else if (stoi(input) == 2)
        {
            if (dispStone)
                dispStone = false;
            else
                dispStone = true;
        }
        else if (stoi(input) == 3)
        {
            if (dispWood)
                dispWood = false;
            else
                dispWood = true;
        }
        else if (stoi(input) == 4)
        {
            if (dispOther)
                dispOther = false;
            else
                dispOther = true;
        }
        else if (stoi(input) == 5)
            mostCommon = true;
        else if (stoi(input) == 6)
            mostCommon = false;
    }

    chunkData.PrintOverviewData(dispOre, dispStone, dispWood, dispOther, mostCommon);

    cout << "Options:\n"
        << "( 1 ) Return to filter menu\n"
        << "( 2 ) Return to beginning\n"
        << "( 3 ) Exit program\n\n"
        << "Select an option: ";
    cin >> input;
    input = filterInput(input, 1, 3);
    cout << string(50, '\n');

    if (stoi(input) == 1)
        ChunkOverviewMode();
    else if (stoi(input) == 2)
        PrintMenu();
    else if (stoi(input) == 3)
        return;
}
void SingleBlockMode()
{
    string input;

    cout << string(50, '\n');
    cout << "~~~~~~~~~~ SINGLE BLOCK ANALYSIS MODE ~~~~~~~~~~\n"
        << "Please Select a block to examine\n"
        << "( 1 ) Stone\n"
        << "( 2 ) Grass\n"
        << "( 3 ) Dirt\n"
        << "( 4 ) Gravel\n"
        << "( 5 ) Wood/Bark\n"
        << "( 6 ) Leaves\n"
        << "( 7 ) Granite\n"
        << "( 8 ) Diorite\n"
        << "( 9 ) Andesite\n"
        << "( 10 ) Coal Ore\n"
        << "( 11 ) Iron Ore\n"
        << "( 12 ) Gold Ore\n"
        << "( 13 ) Redstone Ore\n"
        << "( 14 ) Lapis Lazuli\n"
        << "( 15 ) Diamond Ore\n"
        << "( 16 ) Bedrock\n"
        << "Select an option: ";
    cin >> input;
    input = filterInput(input, 1, 16);

    chunkData.PrintSingleBlock(stoi(input));

    cout << "Options:\n"
        << "( 1 ) Return to single block analysis menu\n"
        << "( 2 ) Return to beginning\n"
        << "( 3 ) Exit program\n\n"
        << "Select an option: ";
    cin >> input;
    input = filterInput(input, 1, 3);
    cout << string(50, '\n');

    if (stoi(input) == 1)
        SingleBlockMode();
    else if (stoi(input) == 2)
        PrintMenu();
    else if (stoi(input) == 3)
        return;
}
void YLevelMode()
{
    string input;

    cout << string(50, '\n');
    cout << "~~~~~~~~~~ Y-LEVEL ANALYSIS MODE ~~~~~~~~~~\n"
        << "( 1 ) Single level analysis\n"
        << "( 2 ) Level range analysis\n"
        << "Select an option: ";
    cin >> input;
    input = filterInput(input, 1, 2);

    if (stoi(input) == 1)
    {
        //Single level analysis
        cout << string(50, '\n');
        cout << "---------------------- Single Level Analysis ----------------------\n"
            << "Y-levels range from 0 (bedrock) to 110 (because let's be real, anything above that is just air)\n"
            << "Please enter the Y-level you would like to analyze: ";
        cin >> input;
        input = filterInput(input, 0, 110);

        chunkData.PrintYLevel(stoi(input));
    }
    else if (stoi(input) == 2)
    {
        //Level range analysis
        string lowerRange;
        string upperRange;

        cout << string(50, '\n');
        cout << "---------------------- Level Range Analysis ----------------------\n"
            << "Y-levels range from 0 (bedrock) to 110 (because let's be real, anything above that is just air)\n"
            << "Please enter the lower Y-level you would like to analyze: ";
        cin >> lowerRange;
        lowerRange = filterInput(lowerRange, 0, 109);

        cout << "Please enter the upper Y-level you would like to analyze: ";
        cin >> upperRange;
        upperRange = filterInput(upperRange, stoi(lowerRange) + 1, 110);

        chunkData.PrintYRange(stoi(lowerRange), stoi(upperRange));
    }

    cout << "Options:\n"
        << "( 1 ) Return to Y-level analysis select\n"
        << "( 2 ) Return to beginning\n"
        << "( 3 ) Exit program\n\n"
        << "Select an option: ";
    cin >> input;
    input = filterInput(input, 1, 3);
    cout << string(50, '\n');

    if (stoi(input) == 1)
        YLevelMode();
    else if (stoi(input) == 2)
        PrintMenu();
    else if (stoi(input) == 3)
        return;
}

void PrintCheckbox(bool isChecked)
{
    cout << "[";

    if (isChecked)
        cout << "x";
    else
        cout << " ";

    cout << "]";
}
string filterInput(string input, int lower, int upper)
{
    //this function checks to make sure the user input is valid based on the 
    //requested parameters, and asks again if it is still invalid

    bool isNumber = true;
    for (int i = 0; i < input.size(); i++)
        if (!std::isdigit(input[i]))
        {
            isNumber = false; 
            break;
        }

    bool isValid = true;
    if (isNumber)
        isValid = stoi(input) >= lower && stoi(input) <= upper;
    if (!isValid || !isNumber)
    {
        string newInput;

        cout << "\nLooks like your input is invalid! Try a number between " << lower << " and " << upper << ": ";
        cin >> newInput;
        cout << endl;

        return filterInput(newInput, lower, upper);
    }
    else
        return input;
}
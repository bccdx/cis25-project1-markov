#include <iostream>
#include <fstream>
using namespace std;

string joinWords(const string words[], int startIndex, int count)
{
	string result = "";

	for (int i = 0; i < count; i++)
	{
		result += words[startIndex + i];
		if (i != count - 1)
		{
			result += " ";
		}
	}

	return result;
}

int readWordsFromFile(string filename, string words[], int maxWords)
{
	ifstream inputFile(filename);

	if (!inputFile.is_open())
	{
		cerr << "Error: File not opened!" << endl;
		return -1;
	}

	int counter = 0;

	while (counter < maxWords && inputFile >> words[counter])
	{
		counter++;
	}

	inputFile.close();

	return counter;
}

int buildMarkovChain(const string words[], int numWords, int order, string prefixes[], string suffixes[], int maxChainSize)
{
	int count = 0;

	for (int i = 0; i < numWords - order; i++)
	{
		string prefix = joinWords(words, i, order);
		string suffix = words[i + order];
		prefixes[count] = prefix;
		suffixes[count] = suffix;
		count++;
		if (count >= maxChainSize)
		{
			break;
		}
	}

	return count;
}

string getRandomSuffix(const string prefixes[], const string suffixes[], int chainSize, string currentPrefix)
{
	return "";
}

string getRandomPrefix(const string prefixes[], int chainSize)
{
	return "";
}

string generateText(const string prefixes[], const string suffixes[], int chainSize, int order, int numWords)
{
	return "";
}
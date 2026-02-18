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
	return 0;
}

int buildMarkovChain(const string words[], int numWords, int order, string prefixes[], string suffixes[], int maxChainSize)
{
	return 0;
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
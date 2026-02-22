#include <iostream>
#include <fstream>
#include <sstream>
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
	int matchCount = 0;

	for (int i = 0; i < chainSize; i++)
	{
		if (prefixes[i] == currentPrefix)
		{
			matchCount++;
		}
	}

	if (matchCount == 0)
	{
		return "";
	}

	int pick = rand() % matchCount;

	int matches = 0;

	for (int i = 0; i < chainSize; i++)
	{
		if (prefixes[i] == currentPrefix)
		{
			if (matches == pick)
			{
				return suffixes[i];
			}
			matches++;
		}
	}

	return "";
}

string getRandomPrefix(const string prefixes[], int chainSize)
{
	int index = rand() % chainSize;
	return prefixes[index];
}

string generateText(const string prefixes[], const string suffixes[], int chainSize, int order, int numWords)
{
	string startingPrefix = getRandomPrefix(prefixes, chainSize);
	string resultString = startingPrefix;
	string currentPrefix = startingPrefix;
	string lastWords[order];
	istringstream iss(startingPrefix);
	string word;

	for (int i = 0; i < order; i++)
	{
		iss >> word;
		lastWords[i] = word;
	}

	for (int i = 0; i < numWords - order; i++)
	{
		string word = getRandomSuffix(prefixes, suffixes, chainSize, currentPrefix);
		if (word == "")
		{
			break;
		}

		resultString += " " + word;

		for (int j = 0; j < (order - 1); j++)
		{
			lastWords[j] = lastWords[j + 1];
		}
		lastWords[order - 1] = word;

		currentPrefix = joinWords(lastWords, 0, order);
	}

	return resultString;
}
#include <iostream>
#include "markov.h"
using namespace std;

int main()
{
	srand(time(0));

	// test joinWords
	string testWords[] = {"the", "cat", "sat", "down"};
	cout << joinWords(testWords, 0, 2) << endl; // Should print: the cat cout << joinWords(testWords, 1, 3) << endl; // Should print: cat sat down
	cout << joinWords(testWords, 1, 3) << endl; // Should print: cat sat down

	// test readWordsFromFile
	string words[1000];
	int count = readWordsFromFile("taylor-swift-all-lyrics.txt", words, 1000);
	cout << "Read " << count << " words" << endl;
	for (int i = 0; i < 10 && i < count; i++)
	{
		cout << words[i] << endl;
	}

	// test buildMarkovChain
	string prefixes[10000], suffixes[10000];
	int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 10000);
	for (int i = 0; i < 20 && i < chainSize; i++)
	{
		cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << endl;
	}

	string prefixes2[10000], suffixes2[10000];
	int chainSize2 = buildMarkovChain(words, count, 2, prefixes2, suffixes2, 10000);
	for (int i = 0; i < 20 && i < chainSize2; i++)
	{
		cout << "[" << prefixes2[i] << "] -> [" << suffixes2[i] << "]" << endl;
	}

	// test getRandomSuffix
	for (int i = 0; i < 10; i++)
	{
		cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << endl;
	}

	// test getRandomPrefix
	for (int i = 0; i < 5; i++)
	{
		cout << getRandomPrefix(prefixes, chainSize) << endl;
	}

	return 0;
}
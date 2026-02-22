#include <iostream>
#include "markov.h"
using namespace std;

int main()
{
	srand(time(0));

	// // test joinWords
	// cout << "*************** test joinWords ***************" << endl;
	// string testWords[] = {"the", "cat", "sat", "down"};
	// cout << joinWords(testWords, 0, 2) << endl; // Should print: the cat cout << joinWords(testWords, 1, 3) << endl; // Should print: cat sat down
	// cout << joinWords(testWords, 1, 3) << endl; // Should print: cat sat down

	// // test readWordsFromFile
	// cout << "*************** test readWordsFromFile ***************" << endl;
	// string words[1000];
	// int count = readWordsFromFile("taylor-swift-all-lyrics.txt", words, 1000);
	// cout << "Read " << count << " words" << endl;
	// for (int i = 0; i < 10 && i < count; i++)
	// {
	// 	cout << words[i] << endl;
	// }

	// // test buildMarkovChain
	// cout << "*************** test buildMarkovChain ***************" << endl;
	// string prefixes[10000], suffixes[10000];
	// int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 10000);
	// for (int i = 0; i < 20 && i < chainSize; i++)
	// {
	// 	cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << endl;
	// }
	// cout << chainSize << endl;

	// string prefixes2[10000], suffixes2[10000];
	// int chainSize2 = buildMarkovChain(words, count, 2, prefixes2, suffixes2, 10000);
	// for (int i = 0; i < 20 && i < chainSize2; i++)
	// {
	// 	cout << "[" << prefixes2[i] << "] -> [" << suffixes2[i] << "]" << endl;
	// }

	// string prefixes3[10000], suffixes3[10000];
	// int chainSize3 = buildMarkovChain(words, count, 3, prefixes3, suffixes3, 10000);
	// for (int i = 0; i < 20 && i < chainSize3; i++)
	// {
	// 	cout << "[" << prefixes3[i] << "] -> [" << suffixes3[i] << "]" << endl;
	// }

	// // test getRandomSuffix
	// cout << "*************** test getRandomSuffix ***************" << endl;
	// for (int i = 0; i < 10; i++)
	// {
	// 	cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << endl;
	// }

	// for (int i = 0; i < 10; i++)
	// {
	// 	cout << getRandomSuffix(prefixes2, suffixes2, chainSize2, "I was") << endl;
	// }

	// for (int i = 0; i < 10; i++)
	// {
	// 	cout << getRandomSuffix(prefixes3, suffixes3, chainSize3, "I couldn't be") << endl;
	// }

	// // test getRandomPrefix
	// cout << "*************** test getRandomPrefix ***************" << endl;
	// for (int i = 0; i < 5; i++)
	// {
	// 	cout << getRandomPrefix(prefixes, chainSize) << endl;
	// }

	// // test generateText
	// cout << "*************** test generateText ***************" << endl;
	// cout << "*************** order = 1 ***************" << endl;
	// string output = generateText(prefixes, suffixes, chainSize, 1, 30);
	// cout << output << endl;
	// cout << "*************** order = 2 ***************" << endl;
	// cout << generateText(prefixes2, suffixes2, chainSize2, 2, 30) << endl;
	// cout << "*************** order = 3 ***************" << endl;
	// cout << generateText(prefixes3, suffixes3, chainSize3, 3, 30) << endl;

	string filename;
	cout << "Enter input filename: " << endl;
	cin >> filename;

	int arraySize = 100000;

	string *words = new string[arraySize];
	string *prefixes = new string[arraySize];
	string *suffixes = new string[arraySize];

	int fileRead = readWordsFromFile(filename, words, arraySize);

	if (fileRead == -1)
	{
		cerr << "Error: Invalid file name, please try running the program again and entering an existing filename in the current directory, and include the extention" << endl;
		return 0;
	}

	int order;
	cout << "Enter order (1, 2, or 3): " << endl;
	cin >> order;
	while (order != 1 && order != 2 && order != 3)
	{
		cout << "Order but be 1, 2, or 3: " << endl;
		cin >> order;
	}

	int numWords;
	cout << "Enter number of words to generate: " << endl;
	cin >> numWords;
	while (numWords <= 0)
	{
		cout << "Number of words to generate must be a positive number " << endl;
		cin >> numWords;
	}

	int chainSize = buildMarkovChain(words, arraySize, order, prefixes, suffixes, arraySize);

	string result = generateText(prefixes, suffixes, chainSize, order, numWords);

	cout << result << endl;

	delete[] words;
	words = nullptr;

	delete[] prefixes;
	prefixes = nullptr;

	delete[] suffixes;
	suffixes = nullptr;

	return 0;
}
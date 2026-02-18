#include <iostream>
#include "markov.h"
using namespace std;

int main()
{
	// test joinWords
	string testWords[] = {"the", "cat", "sat", "down"};
	cout << joinWords(testWords, 0, 2) << endl;			 // Should print: the cat std::cout << joinWords(testWords, 1, 3) << std::endl; // Should print: cat sat down
	cout << joinWords(testWords, 1, 3) << std::endl; // Should print: cat sat down

	// test readWordsFromFile
	string words[1000];
	int count = readWordsFromFile("taylor-swift-all-lyrics.txt", words, 1000);
	cout << "Read " << count << " words" << endl;
	for (int i = 0; i < 10 && i < count; i++)
	{
		cout << words[i] << endl;
	}
	
	return 0;
}
#include <iostream>
#include "markov.h"
using namespace std;

int main()
{
	// test joinWords
	string testWords[] = {"the", "cat", "sat", "down"};
	cout << joinWords(testWords, 0, 2) << std::endl; // Should print: the cat std::cout << joinWords(testWords, 1, 3) << std::endl; // Should print: cat sat down
	cout << joinWords(testWords, 1, 3) << std::endl; // Should print: cat sat down
	
	return 0;
}
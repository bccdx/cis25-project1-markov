#include <iostream>
#include <fstream>
using namespace std;

#include <iostream>
#include <fstream>
#include <string>

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
	inputFile.open(filename);

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
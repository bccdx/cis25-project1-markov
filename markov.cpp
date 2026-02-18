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

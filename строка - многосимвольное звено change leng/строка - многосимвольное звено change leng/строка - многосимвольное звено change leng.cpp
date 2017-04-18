// строка - многосимвольное звено change leng.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
using namespace std;
class Line2Word {
	Line2Word* prev;
	Line2Word* nxt;
	string firstWord;
	string secondWord;
	int countSpaceBefore1;
	int	countSpaceBefore2;
	bool ifEmpty;
	bool freeSpace;//false - 1, true - second
	Line2Word() {
		prev = NULL;
		nxt = NULL;
		countSpaceBefore1 = 0;
		countSpaceBefore2 = 0;
		freeSpace = false;
		ifEmpty = true;
	}
	Line2Word() {
	}
	void Add(string* word, int countSpaceBefore) {

	}
};
int main()
{
    return 0;
}


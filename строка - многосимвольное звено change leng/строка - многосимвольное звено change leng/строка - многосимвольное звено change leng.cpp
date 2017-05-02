// строка - многосимвольное звено change leng.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct Cell {
	Cell* nxt;
	string firstWord;
	string secondWord;
	int countSpaceBefore1;
	int	countSpaceBefore2;

	
	bool addWord(const int spaceBeforeWord, string word, Cell &cell){
		if (cell.freeSpace1Word) {
			cell.firstWord = word;
			cell.countSpaceBefore1 = spaceBeforeWord;
			word[0]==char(1)?cell.freeSpace1Word=true:cell.freeSpace1Word = false;
			cell.full = !(cell.freeSpace1Word||cell.freeSpace2Word);
			return true;
		}
		if (cell.freeSpace2Word) {
			cell.secondWord = word;
			cell.countSpaceBefore2 = spaceBeforeWord;
			word[0] == char(1) ? cell.freeSpace2Word = true : cell.freeSpace2Word = false;
			cell.full = !(cell.freeSpace1Word || cell.freeSpace2Word);
			return true;
		}
		cell.full = true;
		return false;
	}


	bool full;//1 - full 
	bool freeSpace1Word;
	bool freeSpace2Word;

	Cell() {
		nxt = NULL;
		countSpaceBefore1 = 0;
		countSpaceBefore2 = 0;
		freeSpace1Word = true;
		freeSpace2Word = true;
		full = false;
	}
	
	bool push(string word, const int spaceBeforeWord)
	{
		Cell *temp=this;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}
		if (!temp->full) {
			return addWord(spaceBeforeWord, word, *temp);
		}
		Cell *myStack = new Cell; // объявляем новую динамическую переменную типа stek
		temp->nxt = myStack; // связываем новый элемент стека с предыдущим
		return addWord(spaceBeforeWord,word,*myStack);
		return false;
	}
	string get1Word() {
		return this->firstWord;
	}
	string get2Word() {
		return this->secondWord;
	}
	int getCountSpace1() {
		return this->countSpaceBefore1;
	}
	int getCountSpace2() {
		return this->countSpaceBefore2;
	}


};

class Line2Word {
	Cell start;
public:
	Line2Word() {
	}
	void add(string line) {
		line.back() == ' ' ? line += (char)1 : line = line;
		while(line.length()>0) {
			int countSpaceBefore = line.find_first_not_of(" ");
			int nextStart = line.find_first_of(" ", countSpaceBefore + 1);
			string temp = line.substr(countSpaceBefore, nextStart- countSpaceBefore);
			line.erase(0, nextStart);
			start.push(temp, countSpaceBefore);
		}
	}
	
	void printAll() {
		Cell *temp = &start;
		//rewrite
		do {
			if (!temp->freeSpace1Word) {
				cout << temp->get1Word() << temp->getCountSpace1() << endl;
			}
			if (!temp->freeSpace2Word) {
				cout << temp->get2Word() << temp->getCountSpace2() << endl;
			}
			if (temp->firstWord[0] == (char)1) {
				cout << temp->getCountSpace1()<<endl;
			}
			if (temp->secondWord[0] == (char)1) {
				cout << temp->getCountSpace2()<<endl;
			}
			temp = temp->nxt;
		} while (temp != NULL);
		
		

	}

};
int main()
{
	Line2Word line1;
	string temp = "Firstword   asdasd fg sdkufh aesfg sdfg";
	line1.add(temp);
	line1.printAll();
	system("pause");
    return 0;
}


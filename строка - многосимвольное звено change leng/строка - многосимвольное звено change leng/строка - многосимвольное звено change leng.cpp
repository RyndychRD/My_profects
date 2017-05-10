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
	int length() {
		return countSpaceBefore1 +
			countSpaceBefore2 +
			firstWord.length() +
			secondWord.length();
	}
	Cell(Cell *temp) {
		this->countSpaceBefore1 = temp->countSpaceBefore1;
		this->countSpaceBefore2 = temp->countSpaceBefore2;
		this->firstWord = temp->firstWord;
		this->secondWord = temp->secondWord;
		this->freeSpace1Word = temp->freeSpace1Word;
		this->freeSpace2Word = temp->freeSpace2Word;
		this->full = temp->full;
		this->nxt = temp->nxt;
	}

};

struct Line2Word {
	Cell *start;

	Line2Word() {
		start = new Cell;
	}

	~Line2Word() {
		if (&start != NULL) {
			Cell *tmp = start;
			while (tmp != NULL)
			{
				start = start->nxt;
				delete tmp;
				tmp = start;
			}
		}
	}


// all for add
	void add(string line) {
		line.back() == ' ' ? line += (char)1 : line = line;
		while (line.length() > 0) {
			int countSpaceBefore = line.find_first_not_of(" ");
			int nextStart = line.find_first_of(" ", countSpaceBefore + 1);
			string temp = line.substr(countSpaceBefore, nextStart - countSpaceBefore);
			line.erase(0, nextStart);
			push(temp, countSpaceBefore);
		}
	}
	bool addWord(const int spaceBeforeWord, string word, Cell &cell) {
		if (cell.freeSpace1Word) {
			cell.firstWord = word;
			cell.countSpaceBefore1 = spaceBeforeWord;
			word[0] == char(1) ? cell.freeSpace1Word = true : cell.freeSpace1Word = false;
			cell.full = !(cell.freeSpace1Word || cell.freeSpace2Word);
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
	bool push(string word, const int spaceBeforeWord)
	
	{
		Cell *temp = start;

		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}
		if (!temp->full) {
			return addWord(spaceBeforeWord, word, *temp);
		}
		Cell *myStack = new Cell; // объявляем новую динамическую переменную типа stek
		temp->nxt = myStack; // связываем новый элемент стека с предыдущим
		return addWord(spaceBeforeWord, word, *myStack);
		return false;
	}

//+
	void add(Line2Word &line) {
		Cell *temp = line.start;
		while (temp != NULL) {
			temp->firstWord != "" ? push(temp->firstWord, temp->countSpaceBefore1) : false;
			temp->secondWord != "" ? push(temp->secondWord, temp->countSpaceBefore2) : false;
			temp=temp->nxt;
		}
	}
	void add(Cell &tempAdd) {
		Cell *temp = this->start;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}

		temp->nxt = new Cell(tempAdd);
		
	}
	void add(Cell *tempAdd) {
		Cell *temp = this->start;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}

		temp->nxt = new Cell(tempAdd);
	}

	int length() {
		int lengthTemp=0;
		Cell *temp = start;
		while (temp != NULL) {
			lengthTemp += temp->countSpaceBefore1 +
						temp->countSpaceBefore2 +
						temp->firstWord.length() +
						temp->secondWord.length();
			temp = temp->nxt;
		}
		return lengthTemp;
	}
	Cell *last() {
		Cell *temp = start;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}
		return temp;
	}
	
	bool copy(Line2Word &line, const int pos, const int kolvo) {
		//подумать над переприсваиванием строки
		if (this->start == line.start||line.start==NULL||pos<0||kolvo<0||pos>(int)line.length()) { 
			return false;
		}
			this->~Line2Word();
			this->start = new Cell;
			Cell *temp = line.start;
			int tempPos = pos;
			Cell *posStart = temp;
			Cell *posFinish;
			
			while (temp != NULL&&tempPos >= 0) {
				tempPos -= temp->length();
				tempPos < 0 ? posStart = temp : temp=temp->nxt;
			}
	
			int tempKolvo = tempPos + kolvo;
			temp = posStart;
			while (temp != NULL&&tempKolvo > 0) {
				tempKolvo < 0 ? posFinish = temp : temp = temp->nxt;
				tempKolvo -= temp->length();
			} ;
			posFinish = temp;

			if (tempPos < 0 && tempKolvo < 0) {
				tempPos += posStart->length();
				Cell addFirst(posStart);
				bool active = true;
				//боже, помоги мне это забыть
				//добавил первую клетку
				if (tempPos <= addFirst.countSpaceBefore1) {
					addFirst.countSpaceBefore1 -= tempPos;
					active = false;
				}
				if ((tempPos <= addFirst.countSpaceBefore1 + (int)addFirst.firstWord.length()) && active) {
					tempPos -= addFirst.countSpaceBefore1;
					addFirst.countSpaceBefore1 = 0;
					addFirst.firstWord = addFirst.firstWord.substr(tempPos, addFirst.firstWord.length());
					active = false;
				}
				if ((tempPos <= addFirst.countSpaceBefore1 + (int)addFirst.firstWord.length() + addFirst.countSpaceBefore2) && active) {
					addFirst.freeSpace1Word = true;
					addFirst.countSpaceBefore2 -= tempPos - addFirst.countSpaceBefore1 - addFirst.firstWord.length();
					active = false;
				}
				if (active) {
					addFirst.freeSpace1Word = true;
					tempPos -= addFirst.length() + addFirst.secondWord.length();
					addFirst.countSpaceBefore2 = 0;
					addFirst.secondWord = addFirst.secondWord.substr(tempPos, addFirst.secondWord.length());
				}
				addFirst.nxt = NULL;
				this->add(addFirst);

				//добавил промежуток
				temp = posStart->nxt;
				while (temp != posFinish&&posFinish != posStart) {
					this->add(temp);
					temp = temp->nxt;
				}

				//добавил последнюю
				posStart != posFinish ? this->add(posFinish) : false;
				active = true;
				Cell *addLast = this->last();
				tempKolvo = abs(tempKolvo);
				int lengthFirst = addLast->firstWord.length();
				int lengthSecond = addLast->secondWord.length();

				if (tempKolvo <= lengthSecond) {
					addLast->secondWord = addLast->secondWord.substr(0, lengthSecond - tempKolvo);
					active = false;
				}
				if (tempKolvo <= addLast->countSpaceBefore2 + lengthSecond && active) {
					tempKolvo -= lengthSecond;
					addLast->countSpaceBefore2 -= tempKolvo;
					active = false;
				}
				if (tempKolvo <= lengthFirst + lengthSecond + addLast->countSpaceBefore2&&active) {
					addLast->freeSpace2Word = true;
					tempKolvo -= lengthSecond + addLast->countSpaceBefore2;
					addLast->firstWord = addLast->firstWord.substr(0, lengthFirst - tempKolvo);
					active = false;
				}
				if (active) {
					addLast->freeSpace2Word = true;
					addLast->firstWord = "";
					tempKolvo -= lengthFirst + lengthSecond + addLast->countSpaceBefore2;
					addLast->countSpaceBefore1 -= tempKolvo;
				}
				this->add(addLast);
			}
	};

	void printAll() {
		Cell *temp = start;
		//rewrite
		do {
			if (!temp->freeSpace1Word) {
				cout << temp->firstWord << temp->freeSpace1Word <<" ";
			}
			if (!temp->freeSpace2Word) {
				cout << temp->secondWord << temp->freeSpace2Word << " ";
			}
			if (temp->firstWord[0] == (char)1) {
				cout << temp->freeSpace1Word << " ";
			}
			if (temp->secondWord[0] == (char)1) {
				cout << temp->freeSpace1Word << " ";
			}
			temp = temp->nxt;
		} while (temp != NULL);



	}

};
int main()
{
	Line2Word line1,line2;
	string temp = "Firstword 1234 56789 0abcd efghi";
	line2.add(temp);
	line1.add(temp);
	line1.copy(line2, 0, 15);
	line1.printAll();
	system("pause");
	return 0;
}


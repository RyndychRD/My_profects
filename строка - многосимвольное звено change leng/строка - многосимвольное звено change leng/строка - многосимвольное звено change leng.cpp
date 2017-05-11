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

	string convertIntToSpace(int count) {
		string res;
		for (int i = 0; i < count; i++) {
			res += " ";
		}
		return res;
	}
	string convertCellToString(Cell* posStart) {
		return convertIntToSpace(posStart->countSpaceBefore1) +
			posStart->firstWord +
			convertIntToSpace(posStart->countSpaceBefore2) +
			posStart->secondWord;
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
	bool push(string word, const int spaceBeforeWord){
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
			add(temp);
			temp = temp->nxt;
		}
	}
	void add(Cell &tempAdd) {
		!tempAdd.freeSpace1Word ? push(tempAdd.firstWord, tempAdd.countSpaceBefore1) : false;
		!tempAdd.freeSpace2Word ? push(tempAdd.secondWord, tempAdd.countSpaceBefore2) : false;
	}
	void add(Cell *tempAdd) {
		!tempAdd->freeSpace1Word ? push(tempAdd->firstWord, tempAdd->countSpaceBefore1):false;
		!tempAdd->freeSpace2Word ? push(tempAdd->secondWord, tempAdd->countSpaceBefore2) : false;
	}

	int length() {
		int lengthTemp = 0;
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

	bool copy(Line2Word &line,  int pos,  int kolvo) {
		if (line.start == NULL || pos < 0 || kolvo<0 || pos>(int)line.length()) {
			return false;
		}
		if (pos + kolvo > (int)line.length()) {
			kolvo = (int)line.length() - pos;
		}
		Cell *temp = line.start;
		Line2Word lineCopy;
		//if line==this
		if (line.start == this->start) {
			lineCopy.add(line);
			temp = lineCopy.start;
		}
		int tempPos = pos;
		Cell *posStart = temp;
		Cell *posFinish;
		while (temp != NULL&&tempPos >= 0) {
			tempPos -= temp->length();
			tempPos < 0 ? posStart = temp : temp = temp->nxt;
		}

		int tempKolvo = tempPos + kolvo;
		temp = posStart;
		while (temp != NULL&&tempKolvo > 0) {
			tempKolvo < 0 ? posFinish = temp : temp = temp->nxt;
			tempKolvo -= temp->length();
		};
		posFinish = temp;
		//clean this
		this->~Line2Word();
		this->start = new Cell;
		
		if (!(tempPos <= 0 && tempKolvo <= 0)) {
			return false;
		}
		tempPos += posStart->length();
		tempKolvo = abs(tempKolvo);

		//добавил первую клетку
		string stringWholeTempStartCell = convertCellToString(posStart);
		
		if (posStart == posFinish) {
			stringWholeTempStartCell = stringWholeTempStartCell.substr(tempPos, stringWholeTempStartCell.length() - tempKolvo);
			this->add(stringWholeTempStartCell);
		}
		else {
			stringWholeTempStartCell = stringWholeTempStartCell.substr(tempPos, stringWholeTempStartCell.length());
			this->add(stringWholeTempStartCell);
			//добавил промежуток
			temp = posStart->nxt;
			while (temp != posFinish&&posFinish != posStart) {
				this->add(temp);
				temp = temp->nxt;
			}
			//добавил последнюю
			string stringWholeTempFinishCell = convertCellToString(posFinish);
			stringWholeTempFinishCell = stringWholeTempFinishCell.substr(0, stringWholeTempFinishCell.length() - tempKolvo);
			this->add(stringWholeTempFinishCell);
		}
	};

	int search(string line) {
		Line2Word temp;
		temp.add(line);
		return searching(temp);
	}
	int searching(Cell* search, Cell* start) {
		bool result = false;
		string temp = convertCellToString(search);
		int pos=0;
		int tempPos = 0;
		while (start->nxt != NULL&&!result) {
			if (tempPos=(convertCellToString(start) + convertCellToString(start->nxt)).find(temp) == string::npos) {
				pos += start->length();
				start = start->nxt;
			}
			else { 
				pos += tempPos;
				result = true;
			}
		}
		return pos;
	}
	int searching(Line2Word line) {
		bool result = false;
		int pos = -1;
		Cell *temp = this->start;
		Cell *tempIn = line.start;
		while (temp->nxt != NULL  && !result) {
			
		}
	}

	void printAll() {
		Cell *temp = start;
		//rewrite
		do {
			if (!temp->freeSpace1Word) {
				cout << convertIntToSpace(temp->countSpaceBefore1)<< temp->firstWord;
			}
			if (!temp->freeSpace2Word) {
				cout << convertIntToSpace(temp->countSpaceBefore2) << temp->secondWord;
			}
			if (temp->firstWord[0] == (char)1) {
				cout << convertIntToSpace(temp->countSpaceBefore1);
			}
			if (temp->secondWord[0] == (char)1) {
				cout << convertIntToSpace(temp->countSpaceBefore2);
			}
			temp = temp->nxt;
		} while (temp != NULL);



	}

};
int main()
{
	Line2Word line1, line2;
	string temp = "Firstword 1234 56789 0abcd efghi";
	line2.add(temp);
	line1.add(temp);
	line1.copy(line1, 1, 100);
	line1.printAll();
	system("pause");
	return 0;
}


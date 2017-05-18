// строка - многосимвольное звено change leng.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
const char emptySimb = (char)1;
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

class Line2Word {
	Cell *start;
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
	bool addWord(const int spaceBeforeWord, string word, Cell &cell) {
		if (cell.freeSpace1Word) {
			cell.firstWord = word;
			cell.countSpaceBefore1 = spaceBeforeWord;
			cell.freeSpace1Word = false;
			//word[0] == emptySimb ? cell.freeSpace1Word = true : cell.freeSpace1Word = false;
			cell.full = !(cell.freeSpace1Word || cell.freeSpace2Word);
			return true;
		}
		if (cell.freeSpace2Word) {
			cell.secondWord = word;
			cell.countSpaceBefore2 = spaceBeforeWord;
			cell.freeSpace2Word = false;
		 	//word[0] == emptySimb ? cell.freeSpace2Word = true : cell.freeSpace2Word = false;
			cell.full = !(cell.freeSpace1Word || cell.freeSpace2Word);
			return true;
		}
		cell.full = true;
		return false;
	}
	bool push(string word, const int spaceBeforeWord) {
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
	void add(Cell &tempAdd) {
		!tempAdd.freeSpace1Word || tempAdd.countSpaceBefore1 != 0 ? push(tempAdd.firstWord, tempAdd.countSpaceBefore1) : false;
		!tempAdd.freeSpace2Word || tempAdd.countSpaceBefore2 != 0 ? push(tempAdd.secondWord, tempAdd.countSpaceBefore2) : false;
	}
	void add(Cell *tempAdd) {
		!tempAdd->freeSpace1Word||tempAdd->countSpaceBefore1!=0 ? push(tempAdd->firstWord, tempAdd->countSpaceBefore1) : false;
		!tempAdd->freeSpace2Word || tempAdd->countSpaceBefore2 != 0 ? push(tempAdd->secondWord, tempAdd->countSpaceBefore2) : false;

	}
	Cell *last() {
		Cell *temp = start;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}
		return temp;
	}
	int searching(Cell* search, Cell* start) {
		bool result = false;
		string temp = convertCellToString(search);
		int pos = 0;
		int tempPos = 0;
		while (start->nxt != NULL && !result) {
			tempPos = (convertCellToString(start) + convertCellToString(start->nxt)).find(temp);
			if (tempPos == string::npos) {
				pos += start->length();
				start = start->nxt;
			}
			else {
				pos += tempPos;
				result = true;
			}
		}
		if (!result) {
			return -1;
		}
		return pos;
	}

public:
	void operator=(Line2Word in) {
		this->deleteAllCell();
		this->add(in);
	}
	void operator=(string in) {
		this->deleteAllCell();
		this->add(in);
	}
	/*void operator+(Line2Word in) {
		this->add(in);
	}
	void operator+(string in) {
		this->add(in);
	}*/
	friend Line2Word operator+(Line2Word first, Line2Word second);
	friend Line2Word operator+(string first, Line2Word second);
	friend Line2Word operator+(Line2Word first, string second);
	Line2Word() {
		start = new Cell;
	}
	Line2Word(Line2Word &temp) {
		start = new Cell;
		this->add(temp);
	}
	Line2Word(string temp) {
		start = new Cell;
		this->add(temp);
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
	void deleteAllCell() {
		this->~Line2Word();
		this->start = new Cell;

	}
	void add(string line) {
		if (line == "") {
			return;
		}
		line.back() == ' ' ? line += emptySimb : line = line;
		while (line.length() > 0) {
			int countSpaceBefore = line.find_first_not_of(" ");
			int nextStart = line.find_first_of(" ", countSpaceBefore + 1);
			string temp = line.substr(countSpaceBefore, nextStart - countSpaceBefore);
			line.erase(0, nextStart);
			push(temp, countSpaceBefore);
		}
	}
	void add(Line2Word &line) {
		Cell *temp = line.start;
		while (temp != NULL) {
			add(temp);
			temp = temp->nxt;
		}
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
	bool copy(Line2Word &line, int pos, int kolvo) {
		if (line.start == NULL || pos < 0 || kolvo<0 || pos>(int)line.length()) {
			return false;
		}
		if (pos + kolvo >(int)line.length()) {
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
	int searching(string line, int posStart) {
		Line2Word temp;
		temp.add(line);
		return searching(temp,posStart);
	}
	int searching(Line2Word& line,int posStart) {
		if (line.length() == 0) {
			return -1;
		}
		if (line.last()->firstWord[0] == emptySimb) {
			line.last()->firstWord = "";
		}
		if (line.last()->secondWord[0] == emptySimb) {
			line.last()->secondWord = "";
		}
		bool result = false;
		int pos = 0;
		Cell *temp = new Cell(this->start);
		temp->nxt = temp->nxt==NULL?new Cell:temp->nxt;
		Cell *tempIn = new Cell(line.start);
		while (temp->nxt != NULL && !result) {
			pos = searching(tempIn, temp);
			if (pos != -1) {
				int posTempIn = pos;
				bool fail = false;
				while (tempIn != NULL && !fail) {
					posTempIn += tempIn->length();
					fail = (tempIn->nxt == NULL) ? false : posTempIn == searching(tempIn->nxt, tempIn);
					tempIn = tempIn->nxt;
				}
				if (!fail) {
					return pos;
				}
			}
			temp = temp->nxt;
		}
		return -1;
		
	}
	void printAll() {
		Cell *temp = start;
		//rewrite
		do {
			if (temp->firstWord[0] == emptySimb) {
				cout << convertIntToSpace(temp->countSpaceBefore1);
				temp->freeSpace1Word = true;
			}
			if (temp->secondWord[0] == emptySimb) {
				cout << convertIntToSpace(temp->countSpaceBefore2);
				temp->freeSpace2Word = true;
			}

			if (!temp->freeSpace1Word) {
				cout << convertIntToSpace(temp->countSpaceBefore1) << temp->firstWord;
			}
			if (!temp->freeSpace2Word) {
				cout << convertIntToSpace(temp->countSpaceBefore2) << temp->secondWord;
			}
			temp = temp->nxt;
		} while (temp != NULL);
		cout << endl;


	}

};

Line2Word result;
Line2Word operator+(Line2Word first, Line2Word second) {
	result.deleteAllCell();
	result.add(first);
	result.add(second);
	return result;
}
Line2Word operator+(string first, Line2Word second) {
	result.deleteAllCell();
	result.add(first);
	result.add(second);
	return result;
}
Line2Word operator+(Line2Word first, string second) {
	result.deleteAllCell();
	result.add(first);
	result.add(second);
	return result;
}


//string+line, line+string, line+line Template?
void searchAndReplace(Line2Word &line, string lineToFound, string lineToSwap) {
	//find 5 space
	cout << "Error: Line2Word line, string lineToFound, Line2Word lineToSwap argument is required";
	/*Line2Word line1(lineToFound);
	Line2Word line2(lineToSwap);
	searchAndReplace(line, line1, line2);*/
}
void searchAndReplace(Line2Word &line, Line2Word lineToFound, string lineToSwap) {
	cout << "Error: Line2Word line, string lineToFound, Line2Word lineToSwap argument is required";
}
void searchAndReplace(Line2Word &line, string lineToFound, Line2Word lineToSwap) {
	cout << "Error: Line2Word line, string lineToFound, Line2Word lineToSwap argument is required";
}

void searchAndReplace(Line2Word &line, Line2Word lineToFound, Line2Word lineToSwap) {
	int posStart=0;
	int srch = line.searching(lineToFound,posStart);
	if (srch != -1) {
		Line2Word result;
		
		while (srch != -1) {
			Line2Word temp;
			temp.copy(line, posStart, srch-posStart);
			result.add(temp);
			result.add(lineToSwap);
			line.copy(line, srch + lineToFound.length(), line.length());
			srch = line.searching(lineToFound,posStart);
		}
		result.add(line);
		line.deleteAllCell();
		line.add(result);
	}
}

int main()
{
	Line2Word line1="true true true true  true true true true";
	string tmp = "12345 v765432";
	Line2Word temp ("_xchvfdihv true true true true  true true true true");
	Line2Word find (" true true true true  true true true true ");
	(tmp + line1).printAll();
	//search from pos
	system("pause");
	return 0;
}


// Õåøèðîâàíèå.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct HeshCell {
	string cityName;
	int unsigned cityNum;
	unsigned int numTry;
	bool deleteNumTry = false;
	HeshCell() {
		this->cityName = "";
		this->cityNum = 0;
		this->numTry = 0;
	}
	bool operator==(HeshCell a) {
		return ((this->cityName == a.cityName) && (this->cityNum == a.cityNum));
	}
	HeshCell(string cityName, int unsigned cityNum, int unsigned numTry) {
		this->cityName = cityName;
		this->cityNum = cityNum;
		this->numTry = numTry;
	}
	void print() {
		if (this->cityName != "") {
			cout << "Found: cityName:" << this->cityName << " cityNum:" << this->cityNum << endl;
		}
	}
};

struct HeshTabl
{

	const HeshCell emptyCell;
	unsigned int fullness;
	unsigned int countCellIn = 0;
	HeshCell *tabl;
	unsigned int size;

	HeshTabl(unsigned int kolvoCell, unsigned int fullness) {

		this->tabl = new HeshCell[kolvoCell];
		this->size = kolvoCell;
		this->fullness = fullness;
	}

	void reconstructHeshTabl(int kolvoCell, int fullnes) {
		delete[](this->tabl);
		this->fullness = fullnes;
		this->tabl = new HeshCell[kolvoCell];
		this->size = kolvoCell;
		this->countCellIn = 0;
	}
	int heshing(string cityName, int unsigned numTry) {
		numTry--;
		return (((((int)(cityName[0]) + (int)(cityName[1])*2 + (int)(cityName[2])*3))
			+ numTry*numTry) % this->size);

	}

	void pushCell(HeshCell &cell) {
		int unsigned numTry = 1;
		int tempPos = heshing(cell.cityName, numTry);
		while (!(this->tabl[tempPos] == emptyCell)) {
			if (cell.cityName == this->tabl[tempPos].cityName) {
				return ;
			}
			numTry++;
			tempPos = heshing(cell.cityName, numTry);
		}
		cell.numTry = numTry;
		this->tabl[tempPos] = cell;
		this->countCellIn++;

		double k = (double(this->countCellIn) / this->size) * 100;
		if (k > this->fullness) {
			cout << "Table overflow, showing overflowed table" << endl;
			this->printTabl();
			HeshTabl tempTabl(this->size * 3 + 1, fullness);
			for (int i = 0; i < this->size; i++) {
				if (!(this->tabl[i] == emptyCell)) {
					tempTabl.pushCell(this->tabl[i]);
				}
			}
			this->reconstructHeshTabl(tempTabl.size, fullness);
			this->tabl = tempTabl.tabl;
			cout << endl;
			cout << "New table" << endl;
			this->printTabl();
		}
	}

	HeshCell popCell(string cityName) {
		int unsigned numTry = 1;
		int tempPos = heshing(cityName, numTry);
		while ((this->tabl[tempPos].cityName != cityName) && (this->tabl[tempPos].cityName != "")) {
			numTry++;
			tempPos = heshing(cityName, numTry);
		}
		if (this->tabl[tempPos] == emptyCell) {
			cout << cityName << " Not found" << endl;
			HeshCell notFound;
			return notFound;
		}
		else {
			return tabl[tempPos];
		}
	}

	void deleteCell(string cityName) {
		HeshCell foundCell = popCell(cityName);
		if (!(foundCell == emptyCell)) {
			int tryNum = foundCell.numTry;
			int tempCellNum = heshing(foundCell.cityName, tryNum);
			int positionToDelete = tempCellNum;
			if (this->tabl[heshing(foundCell.cityName, tryNum + 1)] == emptyCell) {
				this->tabl[positionToDelete] = emptyCell;
			}
			else {
				while (!(this->tabl[tempCellNum] == emptyCell)) {
					tryNum++;
					tempCellNum = heshing(foundCell.cityName, tryNum);
				}
				tryNum--;
				int lastPos = heshing(foundCell.cityName, tryNum);
				this->tabl[lastPos].numTry = this->tabl[positionToDelete].numTry;
				this->tabl[positionToDelete] = this->tabl[lastPos];
				this->tabl[lastPos] = emptyCell;
			}
			
		}

	}



	void printTabl() {
		for (int i = 0; i < this->size; i++) {
			if (tabl[i].cityName == "") {
				cout << i << " cityName: NOCITY  cityNum:NONUM  numTry:NOTRY" << endl;
			}
			else
			{
				cout << i << " cityName:" << this->tabl[i].cityName << " cityNum:" << this->tabl[i].cityNum << " numTry:" << this->tabl[i].numTry << endl;
			}
		}
	}


};

int main()
{
	int tablSize = 10;
	int fullness = 70;
	int unsigned temp = 1;
	HeshTabl grandTabl(tablSize, fullness);

	string s = "AAXoooooo";

	for (int i = 1; i < 10; i++) {
		HeshCell cellTemp(s, 10 * i, 0);
		grandTabl.pushCell(cellTemp);
		s[0]+=1;
		s[2]-=1;
	}


	grandTabl.printTabl();



	s = "LAMoooooo";
	for (int i = 1; i < 13; i++) {

	//	if (i % 2 == 0) 
		{
			cout << s << endl;
			grandTabl.deleteCell(s);
			//grandTabl.printTabl();
		}
		s[0]-=2;
		s[2]+=2;
	}

	
	grandTabl.printTabl();


	cout << endl << endl;
	s = "LAMoooooo";
	for (int i = 1; i < 13; i++) {

		//	if (i % 2 == 0) 
		{
			HeshCell cellTemp(s, 10 * i, 0);
			grandTabl.pushCell(cellTemp);
		}
		s[0] -= 1;
		s[2] += 1;
	}


	grandTabl.printTabl();

	system("pause");

	return 0;
}

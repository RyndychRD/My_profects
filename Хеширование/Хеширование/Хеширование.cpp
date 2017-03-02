// �����������.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		return (((((int)(cityName[0]) + (int)(cityName[1]) + (int)(cityName[2])))
			+ numTry*numTry) % this->size);

	}
	//checked
	void pushCell(HeshCell &cell) {
		int unsigned numTry = 1;
		int tempPos = heshing(cell.cityName, numTry);
		while (this->tabl[tempPos].cityName != "") {
			numTry++;
			tempPos = heshing(cell.cityName, numTry);
		}
		cell.numTry = numTry;
		this->tabl[tempPos] = cell;
		this->countCellIn++;
		if (numTry >= 17) {
			cout << "";
		}
		double k = (double(this->countCellIn) / this->size) * 100;
		if (k > this->fullness) {
			cout << "Table overflow, showing overflowed table" << endl;
			this->printTabl();
			HeshTabl tempTabl(this->size * 3 + 1, fullness);
			for (int i = 0; i < this->size; i++) {
				if (!(tabl[i].cityName.empty())) {
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
		if (this->tabl[tempPos].cityName == "") {
			cout << cityName << " Not found" << endl;
			HeshCell notFound;
			return notFound;
		}
		else {
			return tabl[tempPos];
		}
	}

	void deleteCell(string cityName) {
		bool numDejavu = false;
		HeshCell foundCell = popCell(cityName);
		HeshCell emptyCell;
		if (foundCell.numTry != 0) {
			int tryNum = foundCell.numTry;
			int previousPos = heshing(foundCell.cityName, tryNum);
			int tempPos = heshing(foundCell.cityName, tryNum++);
			while (this->tabl[tempPos].cityName != "") {
				/*if ((this->tabl[tempPos].numTry < tryNum)) {
					this->tabl[previousPos] = this->tabl[tempPos];
					this->tabl[previousPos].numTry = --tryNum;
					previousPos = tempPos;
					this->tabl[previousPos] = emptyCell;
					this->tabl[tempPos].numTry = --tryNum;
				}
				else {
				*/
				numDejavu = false;
				if ((this->tabl[tempPos].numTry < tryNum)||(tempPos=previousPos)) {
					numDejavu = true;
				}
					this->tabl[previousPos] = this->tabl[tempPos];
					this->tabl[previousPos].numTry = tryNum-1;
					previousPos = tempPos;
					tempPos = heshing(foundCell.cityName, tryNum++);
				
			}
			if (numDejavu) {
				this->tabl[previousPos].cityName = " ";
			}
			else {
				this->tabl[previousPos] = emptyCell;
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
//���������� ��� � ������ �� ������
//������� �������� �� ����� �������� � �������� ������>3
//������� �������� �� �������� �������� = ����� + �����
int main()
{
	ifstream fin("cityToHesh.txt");
	int tablSize = 10;
	int fullness = 70;
	int unsigned temp = 1;
	HeshTabl grandTabl(tablSize, fullness);

	string s = "AAXoooooo";

	for (int i = 1; i < 11; i++) {
		HeshCell cellTemp(s, 10 * i, 0);
		grandTabl.pushCell(cellTemp);
		s[0]++;
		s[2]--;
	}


	grandTabl.printTabl();



	s = "AAXoooooo";
	for (int i = 1; i < 11; i++) {

		if (i % 2 == 0) {
			cout << s << endl;
			grandTabl.deleteCell(s);
			//	grandTabl.printTabl();
		}
		s[0]++;
		s[2]--;
	}


	grandTabl.printTabl();

	system("pause");

	return 0;
}



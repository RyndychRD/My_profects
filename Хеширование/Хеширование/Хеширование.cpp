// Хеширование.cpp: определяет точку входа для консольного приложения.
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
		if (this->numTry != 0) {
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

	void reconstructHeshTabl(int kolvoCell,int fullnes) {
		delete [](this->tabl);
		this->fullness = fullnes;
		this->tabl = new HeshCell[kolvoCell];
		this->size = kolvoCell;
		this->countCellIn = 0;
	}
	int heshing(string cityName, int unsigned numTry) {
		numTry--;
		return (((((int)(cityName[0]) + (int)(cityName[1]) + (int)(cityName[2])) % this->size)
			+ numTry*numTry) % this->size);
	}
	//checked
	void pushCell(HeshCell &cell) {
		int unsigned numTry = 1;
		int tempPos = heshing(cell.cityName, numTry);
		while (this->tabl[tempPos].numTry != 0) {
			numTry++;
			tempPos = heshing(cell.cityName, numTry);
		}
		cell.numTry = numTry;
		this->tabl[tempPos] = cell;
		this->countCellIn++;
	}

	HeshCell popCell(string cityName) {
		int unsigned numTry = 1;
		int tempPos = heshing(cityName, numTry);
		while ((this->tabl[tempPos].cityName != cityName) && (this->tabl[tempPos].numTry != 0)) {
			numTry++;
			tempPos = heshing(cityName, numTry);
		}
		if (this->tabl[tempPos].numTry == 0) {
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
		HeshCell emptyCell;
		if (foundCell.numTry != 0) {
			int tryNum = foundCell.numTry;
			int previousPos = heshing(foundCell.cityName, tryNum);
			int tempPos = heshing(foundCell.cityName, tryNum++);
			if (this->tabl[tempPos].numTry == 0) {
				this->tabl[previousPos] = emptyCell;
			}
			while (this->tabl[tempPos].numTry != 0) {
				this->tabl[previousPos] = this->tabl[tempPos];
				this->tabl[previousPos].numTry = tryNum-2;
				previousPos = tempPos;
				tempPos = heshing(foundCell.cityName, tryNum++);
			}
			this->tabl[previousPos] = emptyCell;
		}
	}



	void printTabl() {
		for (int i = 0; i < this->size; i++) {
			if (tabl[i].numTry == 0) {
				cout << i << " cityName: NOCITY  cityNum:NONUM  numTry:NOTRY" << endl;
			}
			else
			{
				cout << i << " cityName:" << this->tabl[i].cityName << " cityNum:" << this->tabl[i].cityNum << " numTry:" << this->tabl[i].numTry << endl;
			}
		}
	}


};
//переделать инт в номере на стринг
//сделать проверку на колво символов в названии города>3
//сделать проверку на вводисое название = город + номер
int main()
{
	ifstream fin("cityToHesh.txt");
	int tablSize = 10;
	int fullness = 70;
	int unsigned temp = 1;
	HeshTabl grandTabl(tablSize, fullness);

	string s = "AAXoooooo";

	for (int i = 1; i < 11; i++) {
		HeshCell cellTemp(s, 10*i, 0);
		grandTabl.pushCell(cellTemp);
		s[0]++;
		s[2]--;
}


	grandTabl.printTabl();



	 s = "AAXoooooo";

	for (int i = 1; i < 11; i++) {
		HeshCell cellTemp(s, 10 * i, 0);
		
		if (i % 2 == 0) {cout << s << endl; grandTabl.deleteCell(s); }
		s[0]++;
		s[2]--;
	}


	grandTabl.printTabl();






/*	while (!fin.eof()) {
		string cityName;
		int cityNum;
		int const tryNum = 0;
		fin >> cityName >> cityNum;
		cout << cityName << " and hesh:" << grandTabl.heshing(cityName, temp) << endl;
		HeshCell cellTemp(cityName, cityNum, tryNum);
		grandTabl.pushCell(cellTemp);

		int k = (int)((grandTabl.countCellIn / grandTabl.size) * 100);
		if (k > grandTabl.fullness) {
			cout << "Table overflow, showing overflowed table" << endl;
			grandTabl.printTabl();
			HeshTabl tempTabl(grandTabl.size*grandTabl.size + 1, fullness);
			for (int i = 0; i < grandTabl.size; i++) {
				tempTabl.pushCell(grandTabl.tabl[i]);
			}
		    grandTabl.reconstructHeshTabl(tempTabl.size, fullness);
			grandTabl = tempTabl;
			cout << endl;
			cout<<"New table" << endl;
			grandTabl.printTabl();
		}
	}
	grandTabl.popCell("Vladivostok").print();
	grandTabl.popCell("Khabarovsk").print();
	grandTabl.printTabl();
	cout << endl;
	grandTabl.deleteCell("Vladivostok");
	grandTabl.printTabl();*/
	


	system("pause");

	return 0;
}



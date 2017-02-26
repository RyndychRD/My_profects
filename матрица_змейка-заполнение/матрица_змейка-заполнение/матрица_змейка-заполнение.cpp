// матрица_змейка-заполнение.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class matrix {
	int **matr;
	int size;
	int i = 1;
	int j = 1;
	
public:
	matrix(int size) {
		this->size = size;
		this->matr = new int*[size + 2];
		for (int i = 0; i < size + 2; i++) {
			this->matr[i] = new int[size + 2];
		}
		for (int i = 0; i < size ; i++)
			for (int j = 0; j < size ; j++) 
					this->matr[i][j] = 0;
			
	}

	void printMatr(){
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (this->matr[i][j] < 10)
					cout << " ";
				cout << this->matr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void matrConstruct(int size, int i, int j, int count) {
		if ((count) >= this->size*this->size)
			return;
		int k=j;
		int m=i;
		for (k=j; k < size; k++) {
			this->matr[m][k] = count++;
		}
		k--;
		for (m=i+1; m < size; m++) {
			this->matr[m][k] = count++;
		}
		m--;
		for (k--; k >= j; k--) {
			this->matr[m][k] = count++;
		}
		k++;
		for (m--; m > i; m--) {
			this->matr[m][k] = count++;
		}
		m++;
		this->printMatr();
		matrConstruct(size-1, i+1, j+1, count);
	}
};
int main()
{
	int sizeM=10;
	matrix firstTry(sizeM);
	firstTry.matrConstruct(sizeM,0,0,0);
	firstTry.printMatr();
	system("pause");
    return 0;
}


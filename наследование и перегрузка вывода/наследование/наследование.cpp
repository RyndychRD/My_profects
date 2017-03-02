// наследование.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Animal {
public:
	void run() { printf("Run animal"); }

	void go() { printf("go animal"); }

	void speak() { printf("speak animal"); }

	void mult() { printf("mult animal"); }
};

class Dog :public Animal {

};
class Number {
	friend ostream& operator<<(ostream& os, const Number& dt);
protected:
	float value;
public:

	Number(float value) {
		this->value = value;
	}
	Number operator+(Number &b) {
		Number result(0);
		result = this->value + b.value;
		return result;
	}
	Number operator-(Number &b) {
		return (this->value - b.value);
	}
	float getval() {
		return this->value;
	}
};
class Complex :public Number {
	float mnim;
	friend ostream& operator<<(ostream& os, const Complex& dt);
public:
	Complex(float value, float mnim) :Number(value) {
		this->value = value;
		this->mnim = mnim;
	}
	Complex operator+(Complex &b) {
		Complex result(0, 0);
		result.value = this->value + b.value;
		result.mnim = this->mnim + b.mnim;
		return result;
	}
	Complex operator-(Complex &b) {
		Complex result(0, 0);
		result.value = this->value - b.value;
		result.mnim = this->mnim - b.mnim;
		return result;
	}
	Complex operator+(Number &b) {
		Complex result(0, 0);
		result.value= this->value + b.getval();
		result.mnim = this->mnim;
		return result;
	}

	float plus(Number &b) {
		Number::operator+(b);
	}
};


ostream& operator<<(ostream& os, const Number &dt)
{
	os << dt.value << endl;
	return os;
}
ostream& operator<<(ostream& os, const Complex &dt)
{
	os << dt.value << "+i" << dt.mnim << endl;
	return os;
}

int main()
{
	//Dog d;
	//d.run();
	Number a(5);
	Number b(10);
	cout << (a + b);
	Complex comp1(10, 20);
	Complex comp2(20, 30);
	cout << comp1 + comp2;
	cout << a + comp1;
	cout << comp1 + a;
	system("pause");
	return 0;
}


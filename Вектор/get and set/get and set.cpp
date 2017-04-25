// get and set.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

const double PI = 3.1415926535897932384626433832795;
using namespace std;
class Shape {
public:
	virtual double getSquare() { return 0; }
};
class Circle:public Shape {
	int R;
public:
	Circle(int R) {
		this->R = R;
	}
	double getSquare() {
		return PI*R*R;
	}
	   string getName() { 
		   return "Circle";
	   }
};
class Rect :public Shape {
	int height, width;
public:
	Rect(const int &h, const  int &w) {
		this->height = h;
		this->width = w;
	}
	double getSquare() {
		return height*width;
	}
	   string getName() { 
		   return "Rect"; 
	   }
};
class Square :public Rect {
	int w;
	Square(int w) {
		this->w = w;
	}
};


int main()
{
	bool end = false;
	int flag;
	vector<Shape> vect;
	int r = 10;
	int h = 10;
	int w = 20;
	Rect r1(h, w);
	cout << r1.getSquare()<<endl;
	Circle r2(r);
	cout << r2.getSquare() << endl;
	Square r3;
	Shape *c;
	c = &r3;
	cout << c->getSquare() << endl;

	system("pause");
	//while (!(end)) {
	//	cout << "Put var" << endl << "1. push right" << endl << "2. pull right" << endl<<"3. end"<<endl;
	//	cin >> flag;
	//	switch (flag)
	//	{
	//	case(1) :
	//		int putIn;
	//		cin >> putIn;

	//		vect.push_back (putIn);
	//		break;
	//	/*case(2):
	//		cout << vect.back()<<endl;
	//		break;
	//	*/case(3):
	//		end = true;
	//	}

	
    return 0;
}


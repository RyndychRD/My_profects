// ������ ���(������� �����).cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <math.h>
class Shape {
public:
	int x, y, x1, y1;
	int R;
	Shape(int x, int y, int x1, int y1) {
		this->x = x;
		this->y = y;
		this->x1 = x1;
		this->y1 = y1;
	}
	Shape(int R) {
		this->x = x;
		this->y = y;
		this->R = R;
	}
	Shape() {}
};
class Rectangle:public Shape {
	Rectangle(int x, int y, int x1, int y1) : Shape(x, y, x1, y1) {};
	float getSquare() {
		return fabs((this->x - this->x1)*(this->y - this->y1));
	};
};
class Circle: public Shape {	
	Circle(int R) :Shape(R) {};
	float getSquare() {
		return 3.14*this->R*this->R;
	}
};
class Square:public Shape {
	Square(int x, int y, int x1, int y1) : Shape(x, y, x1, y1) {};
	float getSquare() {
		return fabs((this->x - this->x1)*(this->y - this->y1));
	}
};
class ShapeProcessor{
public:
	Shape *vector;

	ShapeProcessor(int size) {};
	~ShapeProcessor();

private:

};

ShapeProcessor::ShapeProcessor(int size)
{

	vector = new Shape[size];
	for (int i = 0; i < size; i++) {
		this->vector[i].x = 1;
		this->vector[i].x = 1;
		this->vector[i].x = 1;
		this->vector[i].x = 1;
		this->vector[i].x = 1;
	}
}

ShapeProcessor::~ShapeProcessor()
{
}
int main()
{
    return 0;
}




class vehicle  // ����� "������������ ��������"
{
	int wheels;
	float weight;
public: // ������ ����������(���������) ������� ������
	virtual void message(void) { cout << "������������ ��������\n"; }
	// �������� ����������� ������� message ������ vehicle � ���������� ���� 
	// �������. ��� ������ ������� message ������ vehicle �� ����� �������� 
	// ����� �������� ������ "������������ ��������"
};

class car : public vehicle // ����� "�������� ������", ��������������  �� 
						   //  ������ "������������ ��������"
{
	int passenger_load;
public: // ������ ����������(���������) ������� ������
	void message(void) { cout << "�������� ������\n"; }
	// �������� ����������� ������� message ������ car � ���������� ���� 
	// �������. ��� ������ ������� message ������ car �� ����� �������� 
	// ����� �������� ������ " �������� ������ "
};

class truck : public vehicle // ����� "�������� ������", ��������������  �� 
							 //  ������ "������������ ��������"
{
	int passenger_load;
	float payload;
public: // ������ ����������(���������) ������� ������
	int passengers(void) { return passenger_load; }
};

class boat : public vehicle // ����� "�����", ��������������  �� 
							//  ������ "������������ ��������"
{
	int passenger_load;
public: // ������ ����������(���������) ������� ������
	int passengers(void) { return passenger_load; }
	void message(void) { cout << "�����\n"; }
	// �������� ����������� ������� message ������ boat � ���������� ���� 
	// �������. ��� ������ ������� message ������ boat �� ����� �������� 
	// ����� �������� ������ "�����"
};

void main() // �������� ����������� ���� ���������
{
	vehicle *unicycle; //  ��������� ���������� unicycle ��� ��������� �� 
					   // ������ ������ vehicle

	unicycle = new vehicle; // ������� ������ ������ vehicle,
							// ��������� unicycle ��������� �� ���� ������
	unicycle->message();   // �������� ����� message �������
	delete unicycle;  // ������� ������ unicycle

					  // ��� ����������� ����� �� 3 ������ ��������� ��������� ������� 
					  // ����� � ��� ���� ��������, ��� ���������� ����� ������������ ������� 
					  // �� car, truck, boat
	unicycle = new car;
	unicycle->message();
	delete unicycle;

	unicycle = new truck;
	unicycle->message();
	delete unicycle;

	unicycle = new boat;
	unicycle->message();
	delete unicycle;
}
// основы ООП(площади фигур).cpp: определяет точку входа для консольного приложения.
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




class vehicle  // класс "транспортное средство"
{
	int wheels;
	float weight;
public: // начало публичного(открытого) раздела класса
	virtual void message(void) { cout << "Транспортное средство\n"; }
	// описание виртуальной функции message класса vehicle и реализация этой 
	// функции. При вызове функции message класса vehicle на экран монитора 
	// будет выведена строка "Транспортное средство"
};

class car : public vehicle // класс "легковая машина", унаследованный  из 
						   //  класса "транспортное средство"
{
	int passenger_load;
public: // начало публичного(открытого) раздела класса
	void message(void) { cout << "Легковая машина\n"; }
	// описание виртуальной функции message класса car и реализация этой 
	// функции. При вызове функции message класса car на экран монитора 
	// будет выведена строка " Легковая машина "
};

class truck : public vehicle // класс "грузовая машина", унаследованный  из 
							 //  класса "транспортное средство"
{
	int passenger_load;
	float payload;
public: // начало публичного(открытого) раздела класса
	int passengers(void) { return passenger_load; }
};

class boat : public vehicle // класс "лодка", унаследованный  из 
							//  класса "транспортное средство"
{
	int passenger_load;
public: // начало публичного(открытого) раздела класса
	int passengers(void) { return passenger_load; }
	void message(void) { cout << "Лодка\n"; }
	// описание виртуальной функции message класса boat и реализация этой 
	// функции. При вызове функции message класса boat на экран монитора 
	// будет выведена строка "Лодка"
};

void main() // основной исполняемый блок программы
{
	vehicle *unicycle; //  описываем переменной unicycle как указатель на 
					   // объект класса vehicle

	unicycle = new vehicle; // Создаем объект класса vehicle,
							// указатель unicycle указывает на этот объект
	unicycle->message();   // вызываем метод message объекта
	delete unicycle;  // удаляем объект unicycle

					  // Все последующие блоки по 3 строки абсолютно идентичны первому 
					  // блоку с той лишь разницей, что изменяется класс создаваемого объекта 
					  // на car, truck, boat
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
#include "stdafx.h" 
#include <iostream> 
using namespace std;

struct ElementLine {
	int element;
	int prioritet;
	ElementLine(int el, int pr) {
		//check >0 
		if (pr < 0) {
			cout << "impossible prioritet" << endl;
			return;
		}
		this->element = el;
		this->prioritet = pr;
	}
	ElementLine() {
		this->element = 0;
		this->prioritet = 0;
	}
	friend bool operator==(ElementLine &temp, ElementLine &temp1);
};
bool operator==(ElementLine &temp, ElementLine &temp1) {
	return ((temp1.element == temp.element) && (temp1.prioritet == temp.prioritet));
}


class LineWithPrior {
public:
	unsigned int head;
	unsigned int tail;
	unsigned int size;
	void incPos(unsigned int &pos) {
		pos = (pos + 1) % this->size;
	}
	void decPos(unsigned int &pos) {
		pos = (pos + this->size - 1) % this->size;
	}
	int elMaxPrior() {
		if (this->line[head] == Nul) {
			return -1;
		}
		int maxPr = this->line[head].prioritet;
		int pos = head;
		unsigned int tempPos = head;
		do {
			incPos(tempPos);
			if (maxPr < this->line[tempPos].prioritet) {
				maxPr = this->line[tempPos].prioritet;
				pos = tempPos;
			}
		} while (tempPos != tail);
		return pos;
	}

	ElementLine *line;
	ElementLine Nul;

	LineWithPrior(unsigned int size) {
		this->line = new ElementLine[size + 1];
		this->line[0] = Nul;
		this->size = size;
		this->tail = 0;
		this->head = 0;
	}
	LineWithPrior(LineWithPrior &temp) {
		this->size = temp.size;
		this->line = new ElementLine[this->size + 1];
		this->line[0] = Nul;
		for (int i = 0; (i < this->size); i++) {
			this->line[i].element = temp.line[i].element;
			this->line[i].prioritet = temp.line[i].prioritet;
		}
		this->tail = temp.tail;
		this->head = temp.head;
	}
	~LineWithPrior() {
		delete[]this->line;
	}
	int showHead() {
		return head;
	}
	void setHead(int headIn) {
		this->head = headIn;
	}
	int showTail() {
		return tail;
	}
	void setTail(int tailIn) {
		this->tail = tailIn;
	}
	ElementLine getEl(int elPos) {
		if (elPos = -1) {
			return Nul;
		}
		return this->line[elPos];
	}
	ElementLine getMaxEl() {
		int elPos = elMaxPrior();
		if (elPos = -1) {
			return Nul;
		}
		return this->line[elPos];
	}
	void addElement(int element, int prior) {
		if ((this->line[tail].prioritet == 0) && (this->size != 0)) {
			this->line[tail].element = element;
			this->line[tail].prioritet = prior;
			tail = (1 + tail) % size;
		}
		else
		{
			cout << "Line is full" << endl;
		}
	}
	int sizeOfLine() {
		if (this->line[head] == Nul) {
			return 0;
		}
		int result = 0;
		unsigned int i = head;
		do {
			result++;
			incPos(i);
		} while (i != tail);
		return result;

	}
	void PrintLn() {
		unsigned int i = head;
		if (this->line[head] == Nul) {
			cout << "Empty queue" << endl;
			return;
		}
		do {
			cout << this->line[i].element << " " << i << "| ";
			incPos(i);
		} while (i != tail);
		cout << endl;
	}
	void deleteEl() {
		int pos;
		pos = elMaxPrior();
		unsigned int posR = pos, posL = pos;
		incPos(posR);
		unsigned int countR = 0, countL = 0;
		if (this->line[head] == Nul) {
			return;
		}
		if ((tail == head) && (tail == pos)) {
			this->line[pos] = Nul;
			incPos(head);
			return;
		}
		while ((posR != tail) && !(this->line[posR] == Nul))
		{
			incPos(posR);
			countR++;
		} while ((posL != head) && !(this->line[posL] == Nul))
		{
			decPos(posL);
			countL++;
		}
		if (countR < countL) {
			posR = pos;
			while (countR > 0) {
				incPos(posR);
				this->line[pos] = this->line[posR];
				pos = posR;
				countR--;
			}
			this->line[posR] = Nul;
			tail = posR;
		}
		else {
			posL = pos;
			while (countL > 0) {
				decPos(posL);
				this->line[pos] = this->line[posL];
				pos = posL;
				countL--;
			}
			this->line[posL] = Nul;
			incPos(posL);
			head = posL;
		}
	}

	LineWithPrior &operator=(LineWithPrior &temp) {
		delete[]this->line;
		this->line = new ElementLine[this->size + 1];
		this->line[0] = Nul;
		if ((this != &temp)&&(temp.size>0)) {
			this->head = 0;
			this->tail = 0;
			unsigned int i = temp.head;
			int count = 0;
			while((count < this->size) && ((count == 0) || (i != temp.tail))){
				this->line[this->tail].element = temp.line[i].element;
				this->line[this->tail].prioritet = temp.line[i].prioritet;
				incPos(this->tail);
				incPos(i);
				count++;

			}
		}
		return *this;
	}
	friend bool operator==(LineWithPrior temp1, LineWithPrior temp2);

};
bool operator ==(LineWithPrior temp1, LineWithPrior temp2) {
	bool flag = true;
	unsigned int i = temp1.showHead();
	unsigned int j = temp2.showHead();

	while ((temp1.getEl(i) == temp2.getEl(j))&&(i!=temp1.tail)) {
		temp1.incPos(i);
		temp1.incPos(j);
	}
	if (i != temp1.showTail()) {
		return false;
	}
	return true;

}

//rewrite with class func
	/*bool flagEqual = true;
		int i = temp1.head;
		int j = temp2.head;
		while((i < temp1.tail) && (j < temp2.tail)){
			++i%=temp1.size;
			++j%=temp2.size;
			flagEqual=temp1.line[i]==temp2.line[j];
		}
		return (i == temp1.tail)&&(j == temp2.tail)&&flagEqual;
	}*/
int main()
{
	LineWithPrior line2(10);
	LineWithPrior line1(12);
	for (int i = 1; i <= 11; i++) {
		line1.addElement(i * 10, i);
		line2.addElement(i * 2, i);
	}
	line1.PrintLn();
	line2.PrintLn();
	if (line1 == line2) {
		cout << "yes";
	}


	//copy constr checked
	/*LineWithPrior line1(0);
	LineWithPrior line1(10);
	for (int i = 1; i <= 11; i++) {
		line1.addElement(i * 10, i);
	}
	LineWithPrior line2(line1);
	line1.PrintLn();
	line2.PrintLn();

*/
	//add/delete/size checked
	/*//for (int i = 1; i <= 11; i++) {
	//	line1.addElement(i*10,  i);
	//}

	for (int i = 1; i <= 11; i++) {
		line1.addElement(1000-i, 100-i);
	}

	line1.PrintLn();

	line1.showHead();
	line1.showTail();
	cout << line1.sizeOfLine() << endl;
	line1.deleteEl();

	line1.deleteEl();

	line1.deleteEl();


	line1.deleteEl();

	line1.deleteEl();

	for (int i = 1; i <= 11; i++) {
		line1.addElement(i , i);
	}


	line1.PrintLn();
	line1.showHead();
	line1.showTail();
	cout << line1.sizeOfLine()<<endl;
	for (int i = 1; i <= 1; i++) {
		line1.deleteEl();
		line1.showHead();
		line1.showTail();
	}
	line1.PrintLn();
	line1.addElement(-1, 1);
	line1.PrintLn();
*/
	system("pause");
	return 0;
}

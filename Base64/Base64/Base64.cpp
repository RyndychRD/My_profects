
#include "stdafx.h"
#include <string.h>
#include <bitset>
#include <iostream>
using namespace std;
char NumToBase64(int chrNum) {
	//rewrite in switch
	if (chrNum < 26) {
		return chrNum + 65;
	}
	if (chrNum < 52) {
		return chrNum + 71;
	}
	if (chrNum < 62) {
		return chrNum - 4;
	}
	if (chrNum = 62) {
		return '+';
	}
	if (chrNum = 63) {
		return '/';
	}
	return '~';
}
int base64ToNum(char baseChar) {
	int baseCharNum = int(baseChar);
	if ((baseCharNum >= (int)("A")) && (baseCharNum <= (int)("Z"))) {
		return baseCharNum - 65;
	}
	if ((baseCharNum >= (int)("a")) && (baseCharNum <= (int)("z"))) {
		return baseCharNum - 97;
	}
	if ((baseCharNum >= (int)("0")) && (baseCharNum <= (int)("9"))) {
		return baseCharNum - 48;
	}
	if (baseCharNum == (int)("+")) {
		return 43;
	}
	if (baseCharNum == (int)("+")) {
		return 47;
	}
}
long asciiToBase64(unsigned int simbCodeOnPos, unsigned int simbCodeOnPosPrev, int pos) {
	bitset<8> simbBoolPos(simbCodeOnPos);
	bitset<8> simbBoolPosPrev(simbCodeOnPosPrev);
	//rewrite with switch case
	if (pos == 0) {
		return(simbBoolPos >> 2).to_ulong();
	}
	if (pos == 1) {
		return(((simbBoolPosPrev << 6) >> 4) | (simbBoolPos >> 4)).to_ulong();
	}
	if (pos == 2) {
		return(((simbBoolPosPrev << 4) >> 2) | (simbBoolPos >> 6)).to_ulong();
	}
	if (pos == 3) {
		return((simbBoolPos << 2).to_ulong());
	}
	
}
char base64ToAscii(unsigned int simbCodeOnPos, unsigned int simbCodeOnPosPost, int pos) {
	bitset<8> simbBoolPos(simbCodeOnPos);
	bitset<8> simbBoolPosPost(simbCodeOnPosPost);
	if (pos == 0) {
		return (simbBoolPos << 2 | simbBoolPosPost >> 4).to_ulong;
	}
	if (pos == 1) {
		return (simbBoolPos << 4 | simbBoolPosPost >> 4).to_ulong;
	}
	if (pos == 2) {
		return (simbBoolPos << 6 | simbBoolPosPost).to_ulong;
	}
}
string codeBase64(string &inStr) {
	string outStr;
	int i = 0;
	while (i < inStr.length()) {
		bool flagMiddle = true; //on 2 simb if true -> left combination, else -> right
		switch (i % 3)
			//check if 2 simb in instr
		{
		case 0: {
			outStr += NumToBase64(asciiToBase64(inStr[i], inStr[i], 0));
			i++;
			break;
		}
		case 1: {
			if (flagMiddle) {
				outStr += NumToBase64(asciiToBase64(inStr[i], inStr[i - 1], 1));
				flagMiddle = !flagMiddle;
			}
			else {
				if ((i + 1) < inStr.length()) {
					outStr += NumToBase64(asciiToBase64(inStr[i + 1], inStr[i], 2));
				}
				else {
					outStr += NumToBase64(asciiToBase64((char)(0), inStr[i], 2));
					outStr += "==";
				}
				flagMiddle = !flagMiddle;
				i++;
			}
			break;
		}
		case 2: {
			outStr += NumToBase64(asciiToBase64(inStr[i], inStr[i], 3));
			i++;
			break;
		}
		}
	}
	return outStr;
}
string decodeBase64(string &inStr) {
	//what if not enough base64 simb
	string outStr;
	int i = 0;
	while (i < inStr.length()) {
		switch (i%4)
		{
		case 0: {
			outStr+=base64ToAscii(base64ToNum(inStr[]))
		}
		default:
			break;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	string inStr = "b";
	cout << codeBase64(inStr);
	system("pause");
	return 0;
}

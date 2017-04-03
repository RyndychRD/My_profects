// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <bitset>
using namespace std;
char NumToBase64(int chrNum){
	if (chrNum<26){
		return chrNum+65;
	}
	if (chrNum<52){
		return chrNum+71;
	}
	if (chrNum<62){
		return chrNum-4;
	}
	if (chrNum=62){
		return '+';
	}
	if (chrNum=63){
		return '/';
	}
	return '~';
}
long asciiToBase64(unsigned int simbCodeOnPos,unsigned int simbCodeOnPosPrev,int pos){
	bitset<8> simbBoolPos(simbCodeOnPos);
	bitset<8> simbBoolPosPrev(simbCodeOnPosPrev);
	if(pos==0){
		return((simbBoolPos>>2).to_ulong);
	}
	if(pos==1){
		return(((simbBoolPosPrev<<6)>>4)|(simbBoolPos>>4)).to_ulong;
	}
	if(pos==2){
		return(((simbBoolPosPrev<<4)>>2)|(simbBoolPos>>6)).to_ulong;
	}
	if(pos==3){
		return((simbBoolPos<<2).to_ulong);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
}


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

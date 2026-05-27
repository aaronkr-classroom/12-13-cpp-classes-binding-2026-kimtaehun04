//Str.cpp
#include <iostream>
#include <iterator>
#include <cstring>

#include "Str.h"

using namespace std;

// 섹션 12.3.2 / 페이지 216
istream& operator>>(istream& is, Str& s){
	s.data.clear(); //Str 객체의 data 벡터를 비운다
	//띄어쓰기까지 문자 읽기
	char c;
	while (is.get(c) && isspace(c)) //공백이 아닌 문자를 만날 때까지 읽는다
		;
	if (is) {
		do s.data.push_back(c); //공백이 아닌 문자를 Str 객체의 data 벡터에 추가한다
		while (is.get(c) && !isspace(c)); //공백이 나올 때까지 계속 읽는다
	
		if (is) //입력 스트림이 유효한 경우
			is.unget(); //마지막으로 읽은 문자를 입력 스트림에 다시 넣는다
	
	}
	return is; //입력 스트림을 반환한다
}
// 섹션 12.3.1 / 페이지 216
ostream& operator<<(ostream& os, const Str& s) {
	for (Str::size_type i = 0; i < s.size(); ++i) {
		os << s[i]; //Str 객체의 각 문자를 출력 스트림에 출력한다
	}
		return os; //출력 스트림을 반환한다
}
//섹션 12.3.3 / 페이지 219
Str operator+(const Str& s, const Str& t) {
	Str r = s;
	r += t;
	return r;
}

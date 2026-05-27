#pragma once
//str.h
#ifndef GUARD_STR_H
#define GUARD_STR_H

#include <algorithm>
#include <iterator>
#include <cstring>
#include "Vec.h"

using namespace std;

class Str {
	// friend 사용하면 private data 접근할 수 있다
	friend istream& operator>>(istream&, Str&); //입력 연산자 const 없다
public:
	typedef Vec<char>::size_type size_type;
	typedef char* iterator;
	typedef const char* const_iterator;
	//생성자들
	//비어 있는 str 객체를 만드는 기본 생성자
	Str() { }// 초기값 없다

	// 2.c의 복사본 n개가 있는 Str 객체를 만드는 생성
	Str(size_type n, char c) : data(n, c) {}

	// 3.null로 끝나는 char 타입의 배열에서 Str 객체를 만드는 생성
	Str(const char* cp) {
		copy(// std::copy()
			cp, cp + strlen(cp), // cp + strlen(cp) : cp의 끝을 가리키는 포인터
			back_inserter(data)// back_inserter() : data의 끝에 요소를 추가하는 반복자
		);
	}
	//4. 반복자 b와 e가 가리키는 범위에서 Str 객체를 만드는 생성
	template <class In> Str(In b, In e) {
		copy(b, e, back_inserter(data));
	}

	//길이 크기 함수
	size_type size() const { return data.size(); }

	//연산자 : 인덱스
	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }

	//연산자 : 결합 
	Str operator+(const Str& s) const {
		Str result = *this; 
		result += s;
		return result;
	}

	Str& operator+=(const Str& rhs) {
		data.insert(data.end(), rhs.data.begin(), rhs.data.end());
		return *this;
	}

	//연습문제 12: 반복자들
	iterator begin() { return data.begin(); }
	iterator end() { return data.end(); }
	typedef Vec<char>::iterator vec_iterator;

	iterator insert(iterator d, iterator b, iterator e) {
		data.insert(d, b, e);
		return d;
	}
private:
	Vec<char> data;
};
ostream& operator<<(ostream& os, const Str&); //출력 연산자
Str operator+(const Str&, const Str&); // Str1 + Str2 결합 연산자 



#endif


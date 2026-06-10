#pragma once
//grad.h
#ifndef GUARD_GRADE_H
#define GUARD_GRADE_H

#include <iostream>
#include "Core.h"

using namespace std;
class Grad : public Core {
public:
	Grad() : thesis(0) {} //빈 객체를 생성
	Grad(istream& is) { read(is); } //스트림을 읽어 객체를 생성
	double grade() const; //성적 계산 함수
	istream& read(istream&);

private:
	double thesis; //논문 점수
};

#endif

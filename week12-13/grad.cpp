//grad.cpp
#include "grad.h"
#include <algorithm>
#include <vector>

istream& read_hw(istream& in, vector<double>& hw)
{
	if (in) {
		hw.clear(); //과제 점수 벡터를 비운다
		double x;
		while (in >> x) { //과제 점수를 읽어서 벡터에 추가한다
			hw.push_back(x);
		}
		in.clear(); //입력 스트림을 다시 유효한 상태로 만든다
	}
	return in; //입력 스트림을 반환한다
}

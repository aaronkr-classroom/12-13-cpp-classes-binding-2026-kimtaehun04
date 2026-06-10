﻿// median.cpp
#include <algorithm>	// sort() 위해
#include <stdexcept>	// domain_error 위해
#include "median.h"

using std::domain_error;	using std::sort;

// median(vector<double>)
double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();

	if (size == 0)
		throw domain_error("Median of empty vector!");

	// 점수를 정렬
	sort(vec.begin(), vec.end()); // hw[0]~hw[size-1]

	// 과제 점수의 중앙값을 구함
	vec_sz mid = size / 2;
	return size % 2 == 0
		? (vec[mid] + vec[mid - 1]) / 2 // 짝수 경우
		: vec[mid]; // 홀수 경우
}

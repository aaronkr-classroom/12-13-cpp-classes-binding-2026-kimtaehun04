﻿// grade.cpp
#include <stdexcept>
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;

// grade(double, double, double)
double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// grade(double, double, const vector<double>&)
double grade(double midterm, double final, const vector<double>& hw) {
	if (hw.size() == 0)
		throw domain_error("No homework entered!");
	return grade(midterm, final, median(hw));
}

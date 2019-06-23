#pragma once
#include <array>
#include <cassert>


constexpr double PI = 3.1415926536;
constexpr double Precision = 1e-3;

typedef std::array<double, 3> double3;
typedef std::array<double, 4> double4;

//判断相等
bool equal(double a, double b, double e = Precision);

//返回a是不是比b小或与b相等
bool lessEqualThan(double a, double b, double e = Precision);

//返回a是不是比b大或与b相等
bool bigerEqualThan(double a, double b, double e = Precision);

//点乘
double dot(const double3& vec1, const double3& vec2);

//是不是同号
bool sameSign(double a, double b);



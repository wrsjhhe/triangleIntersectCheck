#pragma once
#include <array>
#include <cassert>


constexpr double PI = 3.1415926536;
constexpr double Precision = 1e-3;

typedef std::array<double, 3> double3;
typedef std::array<double, 4> double4;

//�ж����
bool equal(double a, double b, double e = Precision);

//����a�ǲ��Ǳ�bС����b���
bool lessEqualThan(double a, double b, double e = Precision);

//����a�ǲ��Ǳ�b�����b���
bool bigerEqualThan(double a, double b, double e = Precision);

//���
double dot(const double3& vec1, const double3& vec2);

//�ǲ���ͬ��
bool sameSign(double a, double b);



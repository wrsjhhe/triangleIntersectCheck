#include "Def.h"

//�ж����
bool equal(double a, double b, double e)
{
	if (a - b < e && a - b > -e)
	{
		return true;
	}

	return false;
}

//����a�ǲ��Ǳ�bС����b���
bool lessEqualThan(double a, double b, double e)
{
	if (equal(a, b, Precision))
	{
		return true;
	}

	return b > a;
}

bool bigerEqualThan(double a, double b, double e)
{
	if (equal(a, b, Precision))
	{
		return true;
	}

	return a > b;
}

bool sameSign(double a, double b)
{
	if (bigerEqualThan(a,0) && bigerEqualThan(b,0))
	{
		return true;
	}

	if (lessEqualThan(a,0) && lessEqualThan(b,0))
	{
		return true;
	}

	return false;
}

//���
double dot(const double3& vec1, const double3& vec2)
{
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}


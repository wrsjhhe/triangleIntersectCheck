#pragma once
#include "Plane.h"



Plane::Plane() :w(0.)
{}
Plane::~Plane() {}



//判断点是否在面上
bool Plane::IsOn(const Vector& _point) const
{
	double val = normal.X() * _point.X() + normal.Y() * _point.Y() + normal.Z() * _point.Z() + w;
	if (equal(val, 0))
	{
		return true;
	}
	return false;
}

//判断是否共面
bool Plane::Coplanar(const Plane& _other) const
{
	Point temp = normal.Cross(_other.normal);;
	if (temp == Vector())
	{
		if (lessEqualThan(0, _other.normal.X() * normal.X()) &&
			lessEqualThan(0, _other.normal.Y() * normal.Y()) &&
			lessEqualThan(0, _other.normal.Z() * normal.Z()))
		{
			if (equal(w, _other.w))
			{
				return true;
			}
		}
		else
		{
			if (equal(w, -_other.w))
			{
				return true;
			}
		}
	}
	return false;
}

Point Plane::Normal() const { return normal; }

bool Plane::operator==(const Plane& _other)
{
	return normal == _other.normal && equal(w, _other.w);
}

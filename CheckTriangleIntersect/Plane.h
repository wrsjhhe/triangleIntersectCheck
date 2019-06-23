#pragma once
#include "Vector.h"

//定义的平面基类
struct Plane
{
	Plane();
	~Plane();

	bool operator==(const Plane& _other);
	//判断点是否在面上
	virtual bool IsOn(const Vector& _point) const;
	//判断是否共面
	virtual bool Coplanar(const Plane& _other) const;

	Point Normal() const;

protected:
	virtual void calcPlane() = 0;

protected:
	Point normal;
	double  w;
};

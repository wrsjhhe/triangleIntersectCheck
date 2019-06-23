#pragma once
#include "Vector.h"

//�����ƽ�����
struct Plane
{
	Plane();
	~Plane();

	bool operator==(const Plane& _other);
	//�жϵ��Ƿ�������
	virtual bool IsOn(const Vector& _point) const;
	//�ж��Ƿ���
	virtual bool Coplanar(const Plane& _other) const;

	Point Normal() const;

protected:
	virtual void calcPlane() = 0;

protected:
	Point normal;
	double  w;
};

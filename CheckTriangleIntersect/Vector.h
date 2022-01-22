#pragma once
#include "Def.h"


//�����������
struct  __declspec(dllexport) Vector
{
	Vector();
	explicit Vector(const double3& _data);
	Vector(const Vector& _point);
	Vector(double _x, double _y, double _z);

	Vector(Vector&& _point);

	~Vector();

	double X() const;
	double Y() const;
	double Z() const;

	void Set(double x, double y, double z);

	//��������
	double Length() const;
	//�����нǣ�����ֵ
	double AngleTo(const Vector& _other) const;

	//��λ��
	Vector& Normalize();

	double3& AsDouble3();

	double Dot(const Vector& _other) const;
	Vector Cross(const Vector& _other) const;

	bool operator==(const Vector& _other);
	bool operator!=(const Vector& _other);
	Vector operator+(const Vector& _other) const;
	Vector operator-(const Vector& _other) const;
	Vector operator*(double k) const;
	double operator*(const Vector& _other) const;
	Vector operator/(double k) const;
	Vector& operator=(const Vector& _other);
	Vector& operator+=(const Vector& _other);

	double3 data;
	static Vector kZero;
};

typedef Vector				Point;
typedef std::array<Point, 2> Point2;
typedef std::array<Point, 3> Point3;
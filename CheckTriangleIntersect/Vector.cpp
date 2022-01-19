#include "Vector.h"
#include <complex>
Vector::Vector() :data(double3{ 0.,0.,0. })
{}

Vector::Vector(const double3& _data) : data(_data)
{}

Vector::Vector(const Vector& _point)
{
	data = _point.data;
}

Vector::Vector(double _x, double _y, double _z) :data({ _x,_y,_z })
{}

Vector::Vector(Vector&& _point) : data(std::move(_point.data))
{

}

Vector::~Vector() {}

double Vector::X() const { return data[0]; }
double Vector::Y() const { return data[1]; }
double Vector::Z() const { return data[2]; }

void Vector::Set(double x, double y, double z)
{
	data = { x,y,z };
}

//向量长度
double Vector::Length() const
{
	return std::sqrt(Dot(*this));
}

//向量夹角，弧度值
double Vector::AngleTo(const Vector& _other) const
{
	assert(!equal(Length(), 0));
	assert(!equal(_other.Length(), 0));
	double cos = (data[0] * _other.data[0] + data[1] * _other.data[1] + data[2] * _other.data[2]) / (Length() *_other.Length());

	return acos(cos);
}

//单位化
Vector& Vector::Normalize()
{
	double len = Length();
	assert(!equal(len, 0));

	data[0] /= len;
	data[1] /= len;
	data[2] /= len;

	return *this;
}

double3& Vector::AsDouble3()
{
	return data;
}


double Vector::Dot(const Vector& _other) const
{
	return data[0] * _other.data[0] + data[1] * _other.data[1] + data[2] * _other.data[2];
}

Vector Vector::Cross(const Vector& _other) const
{
	return { data[1] * _other.data[2] - data[2] * _other.data[1],
			 data[2] * _other.data[0] - data[0] * _other.data[2],
			 data[0] * _other.data[1] - data[1] * _other.data[0] };
}

bool Vector::operator==(const Vector& _other)
{
	return equal(data[0], _other.data[0]) && equal(this->data[1], _other.data[1]) && equal(this->data[2], _other.data[2]);
}

bool Vector::operator!=(const Vector& _other)
{
	return !equal(data[0], _other.data[0]) || !equal(this->data[1], _other.data[1]) || !equal(this->data[2], _other.data[2]);
}

Vector Vector::operator+(const Vector& _other) const
{
	return Vector(data[0] + _other.data[0], data[1] + _other.data[1], data[2] + _other.data[2]);
}

Vector Vector::operator-(const Vector& _other) const
{
	return Vector(data[0] - _other.data[0], data[1] - _other.data[1], data[2] - _other.data[2]);
}

Vector Vector::operator*(double k) const
{
	return Vector(data[0] * k, data[1] * k, data[2] * k);
}

double Vector::operator*(const Vector& _other) const
{
	return Dot(_other);
}

Vector Vector::operator/(double k) const
{
	assert(!equal(k, 0));
	return Vector(data[0] / k, data[1] / k, data[2] / k);
}

Vector& Vector::operator=(const Vector& _other)
{
	data = _other.data;
	return *this;
}

Vector& Vector::operator+=(const Vector& _other)
{
	data[0] = data[0] + _other.data[0];
	data[1] = data[1] + _other.data[1];
	data[2] = data[2] + _other.data[2];
	return *this;
}

Vector Vector::kZero;
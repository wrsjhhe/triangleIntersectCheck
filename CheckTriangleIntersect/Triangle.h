#pragma once
#include "Plane.h"

//定义的三角形类
class Triangle :public Plane
{
public:
	Triangle();
	explicit Triangle(const Point3 & vertices);
	~Triangle();

	void SetVertices(const Point3& _vertices);

	void SetVertices(Point3&& _vertices);

	//判断点是否在三角形内
	virtual bool IsOn(const Point& _point) const override;
	Point3				    Vertices() const;
	const Point3*           VerticesPtr() const;
	Plane&                  Plane();
	Point                   Center() const;
	double                  Area()   const;
private:
	//计算所在平面参数
	virtual void calcPlane() override;

private:
	std::array<Vector, 3> 			m_vertices;
};

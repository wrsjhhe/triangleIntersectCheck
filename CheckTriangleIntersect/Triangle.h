#pragma once
#include "Plane.h"

//�������������
class Triangle :public Plane
{
public:
	Triangle();
	explicit Triangle(const Point3 & vertices);
	~Triangle();

	void SetVertices(const Point3& _vertices);

	void SetVertices(Point3&& _vertices);

	//�жϵ��Ƿ�����������
	virtual bool IsOn(const Point& _point) const override;
	Point3				    Vertices() const;
	const Point3*           VerticesPtr() const;
	Plane&                  Plane();
	Point                   Center() const;
	double                  Area()   const;
private:
	//��������ƽ�����
	virtual void calcPlane() override;

private:
	std::array<Vector, 3> 			m_vertices;
};

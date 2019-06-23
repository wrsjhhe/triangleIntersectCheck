#include "Triangle.h"



Triangle::Triangle() {}
Triangle::Triangle(const Point3& vertices) :
	m_vertices(vertices)
{
	calcPlane();
}
Triangle::~Triangle() {};

void Triangle::SetVertices(const Point3& _vertices)
{
	m_vertices = _vertices;
	calcPlane();
}

void Triangle::SetVertices(Point3&& _vertices)
{
	m_vertices = std::move(_vertices);
	calcPlane();
}

//判断点是否在三角形内
bool Triangle::IsOn(const Point& _point) const
{
	if (!__super::IsOn(_point))
	{
		return false;
	}

	Point v0 = m_vertices[1] - m_vertices[0];
	Point v1 = m_vertices[2] - m_vertices[0];
	Point v2 = _point - m_vertices[0];

	double dot00 = v0.Dot(v0);
	double dot01 = v0.Dot(v1);
	double dot02 = v0.Dot(v2);
	double dot11 = v1.Dot(v1);
	double dot12 = v1.Dot(v2);

	double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

	float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	if (u < 0 || u > 1) // if u out of range, return directly
	{
		return false;
	}

	float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
	if (v < 0 || v > 1) // if v out of range, return directly
	{
		return false;
	}

	return u + v <= 1;
}

Point3				   Triangle::Vertices() const { return m_vertices; }
const Point3*          Triangle::VerticesPtr() const { return &m_vertices; }
Plane&                 Triangle::Plane() { return *this; }

Point Triangle::Center() const
{
	return Point((m_vertices[0] + m_vertices[1] + m_vertices[2]) / 3);
}

double Triangle::Area() const
{
	double area = 0;
	for (unsigned int i = 2; i < m_vertices.size(); i++) {
		const Point &vb = m_vertices[0];
		const Point &v1 = m_vertices[i - 1];
		const Point &v2 = m_vertices[i];
		area += normal.Dot((v1 - vb).Cross(v2 - v1)) / 2.;
	}
	return area;
}

//计算所在平面参数
void Triangle::calcPlane()
{
	Vector vertex;
	for (const auto &v : m_vertices)
		vertex += v * (1.0f / m_vertices.size());

	for (unsigned int i = 0; i < m_vertices.size(); i++)
		normal += (m_vertices[i] - vertex).Cross(m_vertices[(i + 1) % m_vertices.size()] - vertex);

	if (normal == Vector::kZero)
		return;

	normal.Normalize();
	w = -dot(vertex.AsDouble3(), normal.AsDouble3());
}


#include "CheckIntersect.h"
#include "Def.h"

CheckIntersect::CheckIntersect(const Triangle& _tri1, const Triangle& _tri2) : tri1(_tri1), tri2(_tri2)
{}

bool CheckIntersect::DoCheck()
{
	if (CheckUpOrUnderSide())
	{
		return false;
	}

	bool ret = tri1.Coplanar(tri2);
	if (ret)
	{
		return CheckCoplanarSilution();
	}

	return CheckDiffFaceSituation();
}

bool CheckIntersect::_upOrUnderSide(const Triangle& _tri1, const Triangle& _tri2)
{
	Point vec1 = _tri2.Vertices()[0] - _tri1.Vertices()[0];
	Point vec2 = _tri2.Vertices()[1] - _tri1.Vertices()[0];
	Point vec3 = _tri2.Vertices()[2] - _tri1.Vertices()[0];

	Point normal = _tri1.Normal();

	double t1 = vec1.Dot(normal);
	double t2 = vec2.Dot(normal);
	double t3 = vec3.Dot(normal);

	if (t1 * t2 > 0 && t2 * t3 > 0 && t1 * t3 > 0)
	{
		return true;
	}

	return false;
}
//首先判断一个三角形是不是在另一个的所在的面的上面或者下面
//true 在上面或者下面
//false 相交
bool CheckIntersect::CheckUpOrUnderSide()
{
	return _upOrUnderSide(tri1, tri2) || _upOrUnderSide(tri2, tri1);
}


//判断点组pts的点是不是都在linePts异侧
//return true 都在异侧
bool CheckIntersect::_diffSide(const Point3& checkPts, const Point2& linePts, const Vector& normal)
{
	Vector v0 = linePts[1] - linePts[0];
	Vector v1 = checkPts[0] - linePts[0];
	Vector v2 = checkPts[1] - linePts[0];
	Vector v3 = checkPts[2] - linePts[0];
	double h1 = v1.Dot(v0.Cross(normal));
	double h2 = v2.Dot(v0.Cross(normal));
	double h3 = v3.Dot(v0.Cross(normal));

	return !(h1 * h2 > 0 && h2 * h3 > 0 && h1 * h2 > 0);
}

bool CheckIntersect::CheckCoplanarSilution()
{

	//共面的话，先判断一个三角的点是否在另一个内
	bool contain = false;
	Point3 pts1 = tri1.Vertices();
	Point3 pts2 = tri2.Vertices();
	for (int i = 0; i < pts1.size(); ++i)
	{
		if (tri2.IsOn(pts1[i]))
		{
			contain = true;
			break;
		}
	}
	if (contain)
	{
		return true;
	}

	for (int i = 0; i < pts2.size(); ++i)
	{
		if (tri1.IsOn(pts2[i]))
		{
			contain = true;
			break;
		}
	}

	if (contain)
	{
		return true;
	}

	//到这里说明两个三角形的顶点都不在另一个内，再判断顶点是否是在另一个三角形每个边异侧
	//都在的话说明相交，否则不相交
	if (_trianglePointOnOtherDiffSide())
	{
		return true;
	}
	else
	{
		return false;
	}

}

//判断一个三角形点在另一个三边异侧的情况
//return true 在异侧，相交
bool CheckIntersect::_trianglePointOnOtherDiffSide()
{
	const Point3* pPts1 = tri1.VerticesPtr();
	const Point3* pPts2 = tri2.VerticesPtr();

	for (size_t i = 0; i < pPts1->size(); ++i)
	{
		const Point2 line{ pPts1->at(i % pPts1->size()), pPts1->at((i + 1) % pPts1->size()) };
		bool ret = _diffSide(*pPts2, line, tri1.Normal());
		if (!ret)
		{
			return false;
		}
	}

	for (size_t i = 0; i < pPts2->size(); ++i)
	{
		const Point2 *pLine = reinterpret_cast<const Point2*>(pPts2);
		bool ret = _diffSide(*pPts1, *pLine, tri2.Normal());
		if (!ret)
		{
			return false;
		}
	}

	return true;
}

//判断第三步异面情况
bool CheckIntersect::CheckDiffFaceSituation()
{
	if (_checkDiffFaceSituation(tri1,tri2))
	{
		return true;
	}
	else
	{
		return _checkDiffFaceSituation(tri2, tri1);
	}
}

bool CheckIntersect::_checkDiffFaceSituation(const Triangle& _tri1, const Triangle& _tri2)
{
	Point3 pts1 = _tri1.Vertices();
	Point3 pts2 = _tri2.Vertices();

	for (int i = 0; i < pts1.size(); ++i)
	{
		Point& pt = pts1.at(i);

		for (int j = 0; j < pts2.size(); ++j)
		{
			Point& pt1 = pts2.at(j);
			Point& pt2 = pts2.at((j + 1) % pts2.size());
			//判断线段pt2-pt1与pt所在三角形是否相交
			double s1 = (pt1 - pt).Dot(_tri1.Normal());
			double s2 = (pt2 - pt).Dot(_tri1.Normal());

			
			if (!equal(s1,0) || !equal(s2,0))
			{//线段与面不平行
				bool OnSameSide = (s1 * s2 > 0);
				if (OnSameSide)
				{
					//线段在面的一侧，肯定不相交
					continue;
				}
				Vector normal = _tri1.Normal();
				Vector line = pt2 - pt1;
				Point intersection = _calPlaneLineIntersectPoint(normal, pt, line, pt1);
				if (_tri1.IsOn(intersection))
				{
					return true;
				}
			}
			//线段与面共面
			else
			{
				if (_tri1.IsOn(pt1) || _tri1.IsOn(pt2))
				{
					return true;
				}
			}
		}
	}

	return false;
}


Point CheckIntersect::_calPlaneLineIntersectPoint(Vector& planeVector,Point& planePoint,Vector& lineVector,Point& linePoint)
{
	double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t, vpt;
	vp1 = planeVector.AsDouble3()[0];
	vp2 = planeVector.AsDouble3()[1];
	vp3 = planeVector.AsDouble3()[2];
	n1 = planePoint.AsDouble3()[0];
	n2 = planePoint.AsDouble3()[1];
	n3 = planePoint.AsDouble3()[2];
	v1 = lineVector.AsDouble3()[0];
	v2 = lineVector.AsDouble3()[1];
	v3 = lineVector.AsDouble3()[2];
	m1 = linePoint.AsDouble3()[0];
	m2 = linePoint.AsDouble3()[1];
	m3 = linePoint.AsDouble3()[2];
	vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;

	t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;
	Point pt(m1 + v1 * t, m2 + v2 * t, m3 + v3 * t);
	return pt;
}


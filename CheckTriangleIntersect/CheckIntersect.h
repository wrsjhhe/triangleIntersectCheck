#pragma once
#include "Triangle.h"

class CheckIntersect
{
public:
	CheckIntersect(const Triangle& _tri1, const Triangle& _trri2);

	bool DoCheck();


	//第一步首先判断一个三角形是不是在另一个的所在的面的上面或者下面
	//true 在上面或者下面
	//false 相交
	bool CheckUpOrUnderSide();

	bool _upOrUnderSide(const Triangle& _tri1, const Triangle& _tri2);


	//第二步判断一个三角形点在另一个三边异侧的情况
	bool CheckCoplanarSilution();

	//return true 在异侧，相交
	bool _trianglePointOnOtherDiffSide();

	//判断点组pts的点是不是都在linePts异侧
	//return true 都在异侧
	bool _diffSide(const Point3& checkPts, const Point2& linePts, const Vector& normal);

	//第三步判断异面情况
	bool CheckDiffFaceSituation();

	bool _checkDiffFaceSituation(const Triangle& _tri1, const Triangle& _tri2);

	Point _calPlaneLineIntersectPoint(Vector& planeVector, Point& planePoint, Vector& lineVector, Point& linePoint);

private:
	const Triangle& tri1;
	const Triangle& tri2;
};
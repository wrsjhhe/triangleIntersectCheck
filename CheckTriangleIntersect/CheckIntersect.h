#pragma once
#include "Triangle.h"

class CheckIntersect
{
public:
	CheckIntersect(const Triangle& _tri1, const Triangle& _trri2);

	bool DoCheck();


	//��һ�������ж�һ���������ǲ�������һ�������ڵ���������������
	//true �������������
	//false �ཻ
	bool CheckUpOrUnderSide();

	bool _upOrUnderSide(const Triangle& _tri1, const Triangle& _tri2);


	//�ڶ����ж�һ�������ε�����һ�������������
	bool CheckCoplanarSilution();

	//return true ����࣬�ཻ
	bool _trianglePointOnOtherDiffSide();

	//�жϵ���pts�ĵ��ǲ��Ƕ���linePts���
	//return true �������
	bool _diffSide(const Point3& checkPts, const Point2& linePts, const Vector& normal);

	//�������ж��������
	bool CheckDiffFaceSituation();

	bool _checkDiffFaceSituation(const Triangle& _tri1, const Triangle& _tri2);

	Point _calPlaneLineIntersectPoint(Vector& planeVector, Point& planePoint, Vector& lineVector, Point& linePoint);

private:
	const Triangle& tri1;
	const Triangle& tri2;
};
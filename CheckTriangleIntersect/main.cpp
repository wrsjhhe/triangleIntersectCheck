#include "CheckIntersect.h"
#include <iostream>

int main(int argc, char ** argv)
{
	Triangle tri1(Point3{ Point(0,0,2),Point(2,0,2), Point(0,2,2) });
	Triangle tri2(Point3{ Point(1,0,0),Point(1,1,0), Point(1,1,3) });

	CheckIntersect CCheck(tri1,tri2);
	bool ret = CCheck.DoCheck();

	if (ret)
	{
		std::cout << "相交" << std::endl;
	}
	else
	{
		std::cout << "不相交" << std::endl;
	}

	system("pause");
	return 0;
}
#include "../CheckTriangleIntersect/CheckIntersect.h"
#include <iostream>
#include <chrono>
#include <random>
#include "glContext.h"

static std::vector<GLVertex> glVertices
{
	{ { -0.6f, -0.4f ,0.f }, { 1.f, 0.f, 0.f } },
	{ {  0.f, -0.4f ,0.f}, { 0.f, 1.f, 0.f } },
	{ { -0.3f,  0.6f ,0.f}, { 0.f, 0.f, 1.f } },

	{ { 0.f, -0.4f ,0.f }, { 1.f, 0.f, 0.f } },
	{ { 0.6f, -0.4f ,0.f}, { 0.f, 1.f, 0.f } },
	{ { 0.3f,  0.6f ,0.f}, { 0.f, 0.f, 1.f } }
};

static float genRandFloat()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rand_num(seed);  // 大随机数
	std::uniform_int_distribution<int> dist(0, 100);  // 给定范围
	return float(dist(rand_num)) / 100.f;
}

static void convertPoint(vec3& posOut,Point posIn)
{
	posOut[0] = posIn.data[0];
	posOut[1] = posIn.data[1];
	posOut[2] = posIn.data[2];
}

int main(int argc, char ** argv)
{
	GLContext glContext;
	while (!shouldExit)
	{
		if (check)
		{
			Triangle tri1(Point3{
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat())
				});
			Triangle tri2(Point3{
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat())
				});


			CheckIntersect CCheck(tri1, tri2);
			bool ret = CCheck.DoCheck();

			if (ret)
			{
				convertPoint(glVertices.at(0).pos, tri1.Vertices()[0]);
				convertPoint(glVertices.at(1).pos, tri1.Vertices()[1]);
				convertPoint(glVertices.at(2).pos, tri1.Vertices()[2]);
				convertPoint(glVertices.at(3).pos, tri2.Vertices()[0]);
				convertPoint(glVertices.at(4).pos, tri2.Vertices()[1]);
				convertPoint(glVertices.at(5).pos, tri2.Vertices()[2]);

				glContext.UpdateVertices(glVertices);
				std::cout << "检测到相交" << std::endl;
				check = false;
			}
		}
		
		glContext.Draw();
	};
	glContext.Exit();

	return 0;
}
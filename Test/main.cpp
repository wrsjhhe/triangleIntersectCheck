#include "../CheckTriangleIntersect/CheckIntersect.h"
#include <iostream>
#include <chrono>
#include <random>
#include <omp.h> 

const unsigned long long count = 10000;

static float genRandFloat()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rand_num(seed);  // 大随机数
	std::uniform_int_distribution<int> dist(0, 100);  // 给定范围
	return float(dist(rand_num)) / 100.f;
}

int main()
{
	std::cout << "开始生成:" << count << "个三角形" << std::endl;

	std::vector<Triangle> triangles;
	triangles.reserve(count);

	for (size_t i = 0; i < count; i++)
	{
		Triangle tri(Point3{
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat()),
				Point(genRandFloat(),genRandFloat(),genRandFloat())
			});

		triangles.emplace_back(tri);
	}
	std::cout << "开始循环相交判断" << std::endl;
	clock_t start_time = clock();

#pragma omp parallel for  
	for (int i = 0; i < count; i++)
	{
#pragma omp parallel for 
		for (int j = 0; j < count; j++)
		{
			CheckIntersect CCheck(triangles.at(i), triangles.at(j));
			CCheck.DoCheck();
		}
	}
	clock_t end_time = clock();
	std::cout << "检测完成，一共耗时:" << end_time - start_time << "ms" << std::endl;
	std::cout << "检测次数:" << count * count << std::endl;
	std::cout << "平均每次检测耗时:" << double(end_time - start_time) /(count * count) << "ms" << std::endl;
	return 0;
}
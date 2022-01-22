#include "../CheckTriangleIntersect/CheckIntersect.h"
#include <iostream>
#include <chrono>
#include <random>
#include <omp.h> 

const unsigned long long count = 10000;

static float genRandFloat()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rand_num(seed);  // �������
	std::uniform_int_distribution<int> dist(0, 100);  // ������Χ
	return float(dist(rand_num)) / 100.f;
}

int main()
{
	std::cout << "��ʼ����:" << count << "��������" << std::endl;

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
	std::cout << "��ʼѭ���ཻ�ж�" << std::endl;
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
	std::cout << "�����ɣ�һ����ʱ:" << end_time - start_time << "ms" << std::endl;
	std::cout << "������:" << count * count << std::endl;
	std::cout << "ƽ��ÿ�μ���ʱ:" << double(end_time - start_time) /(count * count) << "ms" << std::endl;
	return 0;
}
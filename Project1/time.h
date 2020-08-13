#pragma once
#include <chrono> 

std::chrono::system_clock::time_point start;

// Œv‘ª‚µ‚½‚¢ˆ—

//std::cout << "ÀŠÔ: " << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0) << "•b" << std::endl;

void SetStart()
{
	start = std::chrono::system_clock::now();
}

void Update()
{
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	int t = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
}

void Drow()
{

}


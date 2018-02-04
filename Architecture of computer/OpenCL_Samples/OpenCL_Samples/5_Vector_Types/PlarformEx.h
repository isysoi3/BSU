#pragma once

#include "OpenCL.h"
#include <vector>

class PlarformEx
{
public:
	static std::vector<cl::Platform> GetPlatforms();
	static std::vector<cl::Device> GetDevices(const cl::Platform& platform);
};
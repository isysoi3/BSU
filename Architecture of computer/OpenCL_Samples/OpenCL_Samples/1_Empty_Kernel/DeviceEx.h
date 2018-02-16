#pragma once

#include "OpenCL.h"
#include <vector>

class DeviceEx
{
public:
	static std::string GetVendor(const cl::Device& device);

	static std::string GetName(const cl::Device& device);
};
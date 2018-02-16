#pragma once

#include "OpenCL.h"
#include <vector>
#include "PlarformEx.h"

class DeviceEx
{
public:
	static std::string GetVendor(const cl::Device& device);

	static std::string GetName(const cl::Device& device);

	static cl::Device Find(std::string name);

	static cl::Context CreateContext(const cl::Device& device);
};
#pragma once

#include "OpenCL.h"

class KernelEx
{
public:
	static cl::Kernel BuildFromSource(const cl::Device& device, const cl::Context& context, const std::string& kernelCode, const std::string& kernelName);
};
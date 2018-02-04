#include "KernelEx.h"

cl::Kernel KernelEx::BuildFromSource(const cl::Device& device, const cl::Context& context, const std::string& kernelCode, const std::string& kernelName)
{
	auto source = cl::Program::Sources(1, std::make_pair(kernelCode.c_str(), kernelCode.length() + 1));
	auto program = cl::Program(context, source);
	auto contextDevices = std::vector<cl::Device>{ device };
	program.build(contextDevices);
	return cl::Kernel(program, kernelName.c_str());
}
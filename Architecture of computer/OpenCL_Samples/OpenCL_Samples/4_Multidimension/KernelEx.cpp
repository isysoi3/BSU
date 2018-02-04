#include "KernelEx.h"
#include <fstream>

using namespace std;
using namespace cl;

string LoadText(const string& path)
{
	auto sourceFile = ifstream(path.c_str());
	return string(istreambuf_iterator<char>(sourceFile), istreambuf_iterator<char>());
}

Kernel KernelEx::BuildFromFile(const Device& device, const Context& context, const string& kernelFile, const string& kernelName)
{
	auto kernelSource = LoadText(kernelFile);
	return BuildFromSource(device, context, kernelSource, kernelName);
}

Kernel KernelEx::BuildFromSource(const Device& device, const Context& context, const string& kernelCode, const string& kernelName)
{
	auto source = Program::Sources(1, make_pair(kernelCode.c_str(), kernelCode.length() + 1));
	cl_int error;
	auto program = Program(context, source, &error);
	auto contextDevices = vector<Device>{ device };
	program.build(contextDevices);
	return Kernel(program, kernelName.c_str());
}
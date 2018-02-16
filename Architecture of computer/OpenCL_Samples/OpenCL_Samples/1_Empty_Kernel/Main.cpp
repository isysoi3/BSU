#include "OpenCL.h"
#include "PlarformEx.h"
#include "DeviceEx.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace cl;

class Main
{
public:
	static void Run()
	{
		try
		{
			auto device = FindDevice("Intel");
			RunOnDevice(device);
		}
		catch (const exception &e)
		{
			cerr << e.what() << endl;
		}
	}

private:
	static Device FindDevice(string name)
	{
		for (auto platform : PlarformEx::GetPlatforms())
		{
			for (auto device : PlarformEx::GetDevices(platform))
			{
				auto deviceName = DeviceEx::GetName(device);
				auto vendor = DeviceEx::GetVendor(device);
				if (deviceName.find(name) != string::npos || vendor.find(name) != string::npos)
				{
					return device;
				}
			}
		}

		throw exception("Can't find OpenCL device!");
	}

	static void RunOnDevice(const Device& device)
	{
		auto context = CreateContext(device);
		auto kernelCode = "__kernel void Kernel(void) { }";
		auto kernel = BuildKernel(device, context, kernelCode, "Kernel");

		auto queue = CommandQueue(context, device);
		queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(1));
		queue.finish();
	}

	static Context CreateContext(const Device& device)
	{
		auto contextDevices = vector<Device>();
		contextDevices.push_back(device);
		return Context(contextDevices);
	}

	static Kernel BuildKernel(const Device& device, const Context& context, const string& kernelCode, const string& kernelName)
	{
		auto source = Program::Sources(1, make_pair(kernelCode.c_str(), kernelCode.length() + 1));
		auto program = Program(context, source);
		auto contextDevices = vector<Device>{ device };
		program.build(contextDevices);
		return Kernel(program, kernelName.c_str());
	}
};

int main()
{
	Main::Run();
}
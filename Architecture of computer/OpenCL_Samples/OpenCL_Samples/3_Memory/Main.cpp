#include "OpenCL.h"
#include "DeviceEx.h"
#include <iostream>
#include <vector>
#include "KernelEx.h"
#include <fstream>

using namespace std;
using namespace cl;

class Main
{
public:
	static void Run()
	{
		try
		{
			auto device = DeviceEx::Find("Intel");
			RunOnDevice(device);
		}
		catch (const exception &e)
		{
			cerr << e.what() << endl;
		}
	}

private:
	static void RunOnDevice(const Device& device)
	{
		auto size = 9 * 300;
		auto counters = new int[size] { };

		auto context = DeviceEx::CreateContext(device);
		auto countersBuffer = CreateBuffer(context, counters, size, CL_MEM_READ_WRITE);

		auto kernel = KernelEx::BuildFromFile(device, context, "Kernel.cl", "TestKernel");
		kernel.setArg(0, countersBuffer);

		auto queue = CommandQueue(context, device);
		queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(size / 3), NDRange(size / 9));
		queue.finish();
		ReadFromBuffer(queue, counters, size, countersBuffer);

		Print(counters, size);
		delete[] counters;
	}

	static Buffer CreateBuffer(const Context& context, int* array, int size, int accessFlag)
	{
		return Buffer(context, accessFlag | CL_MEM_COPY_HOST_PTR, size * sizeof(int), array);
	}

	static void ReadFromBuffer(const CommandQueue& queue, int* array, int size, const Buffer& buffer)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, size * sizeof(int), array);
	}

	static void Print(int* counters, const int size)
	{
		for (auto i = 0; i < size; i += 3)
		{
			cout << "counters[" << i << "...] = " << counters[i] << ", " << counters[i + 1] << ", " << counters[i + 2] << endl;
		}
	}
};

int main()
{
	Main::Run();
}
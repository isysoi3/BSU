#include "OpenCL.h"
#include "DeviceEx.h"
#include <iostream>
#include "KernelEx.h"
#include "Matrix.h"
#include <iomanip>

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
		srand(0);
		auto n = 4 * 2;
		auto m = 4 * 2;
		auto l = 4 * 2;
		auto m1 = CreateMatrix(n, m);
		auto m2T = CreateMatrix(l, m);
		Print(m1);
		Print(m2T);

		auto context = DeviceEx::CreateContext(device);
		auto m1Buffer = CreateBuffer(context, m1, CL_MEM_READ_ONLY);
		auto m2TBuffer = CreateBuffer(context, m2T, CL_MEM_READ_ONLY);

		RunKernel(device, context, m1Buffer, m2TBuffer, n, m, l, "TestKernel3");
		RunKernel(device, context, m1Buffer, m2TBuffer, n, m, l, "TestKernel4");

		m1.Dispose();
		m2T.Dispose();
	}

	static void RunKernel(const Device& device, const Context& context, Buffer m1Buffer, Buffer m2TBuffer, int n, int m, int l, string kernelName)
	{
		auto m3 = Matrix(n, l, new int[n * l]{});
		auto m3Buffer = CreateBuffer(context, m3, CL_MEM_READ_WRITE);

		auto kernel = KernelEx::BuildFromFile(device, context, "Kernel.cl", kernelName);
		kernel.setArg(0, m1Buffer);
		kernel.setArg(1, m2TBuffer);
		kernel.setArg(2, m3Buffer);
		kernel.setArg(3, n);
		kernel.setArg(4, m);
		kernel.setArg(5, l);

		auto event = Event();
		auto queue = CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);
		queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(m3.Rows, m3.Columns), NullRange, nullptr, &event);
		event.wait();
		queue.finish();

		auto startTime = event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
		auto endTime = event.getProfilingInfo<CL_PROFILING_COMMAND_END>();
		cout << "Time: " << fixed << setprecision(3) << (endTime - startTime) / 1000000.0 << " ms" << endl;

		ReadFromBuffer(queue, m3, m3Buffer);

		Print(m3);
	}

	static Matrix CreateMatrix(int n, int m)
	{
		auto size = n * m;
		auto matrix = new int[size];
		for (auto k = 0; k < size; ++k)
		{
			matrix[k] = -1 + rand() % 3;
		}
		return Matrix(n, m, matrix);
	}

	static void Print(Matrix matrix)
	{
		// return; //

		for (auto i = 0; i < matrix.Rows; ++i)
		{
			for (auto j = 0; j < matrix.Columns; ++j)
			{
				cout << matrix.Get(i, j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	static Buffer CreateBuffer(const Context& context, Matrix matrix, int accessFlag)
	{
		return Buffer(context, accessFlag | CL_MEM_COPY_HOST_PTR, matrix.Rows * matrix.Columns * sizeof(int), matrix.Data);
	}

	static void ReadFromBuffer(const CommandQueue& queue, Matrix matrix, const Buffer& buffer)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, matrix.Rows * matrix.Columns * sizeof(int), matrix.Data);
	}
};

int main()
{
	Main::Run();
}
#include "OpenCL.h"
#include "DeviceEx.h"
#include <iostream>
#include "KernelEx.h"
#include <iomanip>

using namespace std;
using namespace cl;

class Matrix
{
public:
	int Rows;
	int Columns;
	int* Data;

	Matrix(int rows, int columns, int* data) : Rows(rows), Columns(columns), Data(data) { }

	void Dispose()
	{
		delete[] Data;
		Data = nullptr;
	}

	int Get(int i, int j) const
	{
		return Data[i * Columns + j];
	}

	Matrix Transpose() const
	{
		auto data = new int[Rows * Columns];
		for (auto i = 0; i < Rows; ++i)
		{
			for (auto j = 0; j < Columns; ++j)
			{
				data[j * Rows + i] = Get(i, j);
			}
		}
		return Matrix(Columns, Rows, data);
	}
};

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
		auto n = 3000;
		auto m = 500;
		auto l = 2000;
		auto m1 = CreateMatrix(n, m);
		auto m2 = CreateMatrix(m, l);
		auto m2T = m2.Transpose();
		Print(m1);
		Print(m2);
		Print(m2T);

		auto context = DeviceEx::CreateContext(device);
		auto m1Buffer = CreateBuffer(context, m1, CL_MEM_READ_ONLY);
		auto m2Buffer = CreateBuffer(context, m2, CL_MEM_READ_ONLY);
		auto m2TBuffer = CreateBuffer(context, m2T, CL_MEM_READ_ONLY);

		RunKernel(device, context, m1Buffer, m2Buffer, n, m, l, "TestKernel1");
		RunKernel(device, context, m1Buffer, m2Buffer, n, m, l, "TestKernel2");
		RunKernel(device, context, m1Buffer, m2TBuffer, n, m, l, "TestKernel3");

		m1.Dispose();
		m2.Dispose();
		m2T.Dispose();
	}

	static void RunKernel(const Device& device, const Context& context, Buffer m1Buffer, Buffer m2Buffer, int n, int m, int l, string kernelName)
	{
		auto m3 = Matrix(n, l, new int[n * l]{});
		auto m3Buffer = CreateBuffer(context, m3, CL_MEM_READ_WRITE);

		auto kernel = KernelEx::BuildFromFile(device, context, "Kernel.cl", kernelName);
		kernel.setArg(0, m1Buffer);
		kernel.setArg(1, m2Buffer);
		kernel.setArg(2, m3Buffer);
		kernel.setArg(3, n);
		kernel.setArg(4, m);
		kernel.setArg(5, l);

		auto event = Event();
		auto queue = CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE);
		queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(m3.Rows, m3.Columns), NullRange, nullptr, &event);
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
		return; //

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
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
private:

	static void ReadFile(ifstream & in, unsigned int * Matrix, short int& V, short int& H)
	{
		in.read((char *)&V, sizeof(V));
		in.read((char *)&H, sizeof(H));
		Matrix = new unsigned int[V*H];
		for (int i = 0; i < V; i++)
			for (int j = 0; j < H; j++)
				in.read((char *)&Matrix[i*H + j], sizeof(unsigned int));
	}

	static void Print(ofstream & out, unsigned int * Matrix, unsigned short int V, unsigned short int H)
	{
		out.write((char*)&V, sizeof(unsigned short int));
		out.write((char*)&H, sizeof(unsigned short int));
		for (int i = 0; i < V; i++)
			for (int j = 0; j < H; j++)
				out.write((char*)&Matrix[i*H + j], sizeof(unsigned int));
	}


	static void RunOnDevice(const Device& device, unsigned int * Matrix, unsigned short int V, unsigned short int H, unsigned int color)
	{
		auto context = DeviceEx::CreateContext(device);
		auto matrixBuffer = CreateBuffer(context, Matrix, V, H, CL_MEM_READ_WRITE);

		auto kernelCode = LoadText("Kernel.cl");
		auto kernel = KernelEx::BuildFromSource(device, context, kernelCode, "TestKernel");
		kernel.setArg(0, matrixBuffer);
		kernel.setArg(1, V);
		kernel.setArg(2, H);
		kernel.setArg(3, color);

		auto queue = CommandQueue(context, device);
		queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(V, H));
		queue.finish();

		ReadFromBuffer(queue, Matrix, V, H, matrixBuffer);
	}

	static void ReadFromBuffer(const CommandQueue& queue, unsigned int * matrix, unsigned int V, unsigned int H, const Buffer& buffer)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, V * H * sizeof(unsigned int), matrix);
	}

	static Buffer CreateBuffer(const Context& context, unsigned int * Matrix, unsigned short int v, unsigned short int h, int accessFlag)
	{
		return Buffer(context, accessFlag | CL_MEM_COPY_HOST_PTR, v*h*(sizeof(unsigned int)), Matrix);
	}

	static string LoadText(const string& path)
	{
		auto sourceFile = ifstream(path.c_str());
		return string(istreambuf_iterator<char>(sourceFile), istreambuf_iterator<char>());
	}

	static void ReadFromBuffer(const CommandQueue& queue, float* array, int size, const Buffer& buffer)
	{
		queue.enqueueReadBuffer(buffer, CL_TRUE, 0, size * sizeof(float), array);
	}

	
	static void ReleaseMemory(unsigned int ** Matrix, unsigned short int V)
	{
		for (int i = 0; i < V; i++)
		{
			delete[] Matrix[i];
		}
		delete[] Matrix;
	}

public:
	static void Run(string inputPath, string outputPath, unsigned int color)
	{
		short int V, H;
		unsigned int * Matrix;

		ifstream in(inputPath, ios::binary);
		ofstream out(outputPath, ios::binary);

		ReadFile(in, Matrix, V, H);

		try
		{
			auto device = DeviceEx::Find("Intel");
			RunOnDevice(device, Matrix, V, H, color);
			Print(out, Matrix, V, H);
		}
		catch (const exception &e)
		{
			cerr << e.what() << endl;
		}
		//ReleaseMemory(Matrix, V);
	}

};

int  main(int argc, char* argv[])
{
	if (argc < 4)
		return 0;
	Main::Run(argv[1], argv[2], std::atoi(argv[3]));
	system("pause");
}

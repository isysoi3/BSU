#include "OpenCL.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
using namespace cl;

class Main
{
public:
	static void Run()
	{
		for (auto platform : GetPlatforms())
		{
			for (auto device : GetDevices(platform))
			{
				Hi(device);
			}
		}
	}

private:
	static vector<Platform> GetPlatforms()
	{
		auto platforms = vector<Platform>();
		Platform::get(&platforms);
		return platforms;
	}

	static vector<Device> GetDevices(const Platform& platform)
	{
		auto devices = vector<Device>();
		platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
		return devices;
	}

	static void Hi(const Device& device)
	{
		cout << "Hi from " << GetDeviceVendor(device) << "'s " << GetDeviceName(device) << endl;
	}

	static string GetDeviceVendor(const Device& device)
	{
		return string(device.getInfo<CL_DEVICE_VENDOR>());
	}

	static string GetDeviceName(const Device& device)
	{
		return string(device.getInfo<CL_DEVICE_NAME>());
	}
};

int main()
{
	Main::Run();
}
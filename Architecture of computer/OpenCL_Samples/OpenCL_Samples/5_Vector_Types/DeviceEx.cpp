#include "DeviceEx.h"

using namespace std;
using namespace cl;

string DeviceEx::GetVendor(const Device& device)
{
	return string(device.getInfo<CL_DEVICE_VENDOR>());
}

string DeviceEx::GetName(const Device& device)
{
	return string(device.getInfo<CL_DEVICE_NAME>());
}

Device DeviceEx::Find(string name)
{
	for (auto platform : PlarformEx::GetPlatforms())
	{
		for (auto device : PlarformEx::GetDevices(platform))
		{
			auto deviceName = GetName(device);
			auto vendor = GetVendor(device);
			if (deviceName.find(name) != string::npos || vendor.find(name) != string::npos)
			{
				return device;
			}
		}
	}

	throw exception("Can't find OpenCL device!");
}

Context DeviceEx::CreateContext(const Device& device)
{
	auto contextDevices = vector<Device>();
	contextDevices.push_back(device);
	return Context(contextDevices);
}